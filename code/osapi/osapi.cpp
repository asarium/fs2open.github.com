/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

#include <stdio.h>
#include <fcntl.h>
#include <stdarg.h>

#include "globalincs/pstypes.h"
#include "io/key.h"
#include "palman/palman.h"
#include "io/mouse.h"
#include "osapi/outwnd.h"
#include "sound/sound.h"
#include "freespaceresource.h"
#include "playerman/managepilot.h"
#include "io/joy.h"
#include "io/joy_ff.h"
#include "gamesequence/gamesequence.h"
#include "freespace.h"
#include "osapi/osregistry.h"
#include "cmdline/cmdline.h"
#include "sound/voicerec.h"
#include "graphics/2d.h"
#include "cmdline/cmdline.h"

#ifdef __linux__
#include <execinfo.h>
#endif

#define THREADED	// to use the proper set of macros
#include "osapi/osapi.h"

#include "SDL_syswm.h"


// used to be a THREADED define but only use multiple process threads if this is defined
// NOTE: may hang if set
//#define THREADED_PROCESS

// ----------------------------------------------------------------------------------------------------
// PLATFORM SPECIFIC FUNCTION FOLLOWING
//


#ifdef WIN32

// Windows specific includes
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <io.h>
#include <winsock.h>
#include <direct.h>

// For FRED
void os_set_window_from_hwnd(HWND handle)
{
	SDL_InitSubSystem(SDL_INIT_VIDEO);

	if (SDL_GL_LoadLibrary(NULL) < 0)
		Error(LOCATION, "Failed to load OpenGL library: %s!", SDL_GetError());

	SDL_Window* window = SDL_CreateWindowFrom((void*) handle);

	os_set_window(window);
}

// go through all windows and try and find the one that matches the search string
BOOL __stdcall os_enum_windows( HWND hwnd, TCHAR * search_string )
{
	TCHAR tmp[128];
	int len;

	len = GetWindowText( hwnd, tmp, 127 );
	 
	if ( len )	{
		if ( wcsstr( tmp, search_string ))	{
			Os_debugger_running = 1;		// found the search string!
			return FALSE;	// stop enumerating windows
		}
	}

	return TRUE;	// continue enumeration
}

// Fills in the Os_debugger_running with non-zero if debugger detected.
void os_check_debugger()
{
	HMODULE hMod;
	TCHAR search_string[256];
	TCHAR myname[128];
	int namelen;
	TCHAR * p;

	Os_debugger_running = 0;		// Assume its not

	// Find my EXE file name
	hMod = GetModuleHandle(NULL);
	if ( !hMod ) return;
	namelen = GetModuleFileName( hMod, myname, 127 );	
	if ( namelen < 1 ) return;
	
	// Strip off the .EXE
	p = wcsstr( myname, L".exe" );
	if (!p) return;
	*p = '\0';

	// Move p to point to first letter of EXE filename
	while( (*p!='\\') && (*p!='/') && (*p!=':') )
		p--;
	p++;
	if ( wcslen(p) < 1 ) return;

	// Build what the debugger's window title would be if the debugger is running...
	swprintf( search_string, L"[run] - %s -", p );

	// ... and then search for it.
	EnumWindows( (int (__stdcall *)(struct HWND__ *,long))os_enum_windows, (long)&search_string );
}

void os_set_process_affinity()
{
	HANDLE pHandle = GetCurrentProcess();
	DWORD pMaskProcess = 0, pMaskSystem = 0;

	if ( GetProcessAffinityMask(pHandle, &pMaskProcess, &pMaskSystem) ) {
		// only do this if we have at least 2 procs
		if (pMaskProcess >= 3) {
			// prefer running on the second processor by default
			pMaskProcess = os_config_read_uint(NULL, "ProcessorAffinity", 2);

			if (pMaskProcess > 0) {
				SetProcessAffinityMask(pHandle, pMaskProcess);
			}
		}
	}
}

#endif // WIN32


// ----------------------------------------------------------------------------------------------------
// OSAPI DEFINES/VARS
//

static SDL_Window* main_window = NULL;

// os-wide globals
static bool			fAppActive = false;
static char			szWinTitle[128];
static char			szWinClass[128];
static int			Os_inited = 0;

static SDL_mutex* Os_lock;

int Os_debugger_running = 0;

// ----------------------------------------------------------------------------------------------------
// OSAPI FORWARD DECLARATIONS
//

// called at shutdown. Makes sure all thread processing terminates.
void os_deinit();

// ----------------------------------------------------------------------------------------------------
// OSAPI FUNCTIONS
//

namespace os
{
	SCP_map<SDL_EventType, SCP_map<int, std::pair<std::function<bool(const SDL_Event&)>, size_t>>> eventListeners;

	size_t nextIdentifier = 0;

	int addEventListener(SDL_EventType type, int weigth, const std::function<bool(const SDL_Event&)>& listener)
	{
		Assertion(listener, "Listener pointer is not valid!");

		auto iter = eventListeners.find(type);

		if (iter == eventListeners.end())
		{
			iter = eventListeners.insert(std::make_pair(type, SCP_map<int,
				std::pair<std::function<bool(const SDL_Event&)>, size_t>>())).first;
		}

		size_t identifier = nextIdentifier++;

		iter->second.insert(std::make_pair(weigth, std::make_pair(listener, identifier)));

		return identifier;
	}

	bool removeEventListener(size_t identifer)
	{
		for (auto& pair : eventListeners)
		{
			auto& map = pair.second;

			for (auto iter = map.cbegin(); iter != map.cend();)
			{
				if (iter->second.second == identifer)
				{
					map.erase(iter);
					return true;
				}
				else
				{
					++iter;
				}
			}
		}

		return false;
	}
}

namespace
{
	void initializeEventHandling()
	{
		os::addEventListener(SDL_WINDOWEVENT, os::DEFAULT_LISTENER_WEIGHT, [](const SDL_Event& event)
		{
			if (event.window.windowID == SDL_GetWindowID(os_get_window())) {
				switch (event.window.event) {
				case SDL_WINDOWEVENT_MINIMIZED:
				case SDL_WINDOWEVENT_FOCUS_LOST:
				{
					if (fAppActive) {
						if (!Cmdline_no_unfocus_pause) {
							game_pause();
						}

						fAppActive = false;
					}
					break;
				}
				case SDL_WINDOWEVENT_MAXIMIZED:
				case SDL_WINDOWEVENT_RESTORED:
				case SDL_WINDOWEVENT_FOCUS_GAINED:
				{
					if (!fAppActive) {
						if (!Cmdline_no_unfocus_pause) {
							game_unpause();
						}

						fAppActive = true;
					}
					break;
				}
				case SDL_WINDOWEVENT_CLOSE:
					gameseq_post_event(GS_EVENT_QUIT_GAME);
					break;
				}
			}

			gr_activate(fAppActive);

			return true;
		});
	}
}

// detect home/base directory  (placeholder for possible future Win32 userdir support, just returns current directory for now)
char Cur_path[MAX_PATH_LEN];
const char *detect_home(void)
{
#ifdef WIN32
	if ( !cfile::getRootDir().empty() )
		return cfile::getRootDir().c_str();

	TCHAR path[MAX_PATH_LEN];
	memset(path, 0, sizeof(path));
	GetCurrentDirectory(MAX_PATH_LEN - 1, path);

	wcstombs(Cur_path, path, MAX_PATH_LEN - 1);

	return Cur_path;
#else
	return (getenv("HOME"));
#endif
}

// initialization/shutdown functions -----------------------------------------------

// If app_name is NULL or ommited, then TITLE is used
// for the app name, which is where registry keys are stored.
void os_init(const char * wclass, const char * title, const char *app_name, const char *version_string )
{
	// create default ini entries for the user
	if (os_config_read_string(NULL, NOX("VideocardFs2open"), NULL) == NULL)
		os_config_write_string(NULL, NOX("VideocardFs2open"), NOX("OGL -(640x480)x16 bit"));

	os_init_registry_stuff(Osreg_company_name, title, version_string);

	strcpy_s( szWinTitle, title );
	strcpy_s( szWinClass, wclass );	

	Os_lock = SDL_CreateMutex();

	mprintf(("  Initializing SDL...\n"));

	if (SDL_Init(SDL_INIT_EVENTS) < 0)
	{
		fprintf(stderr, "Couldn't init SDL: %s", SDL_GetError());
		mprintf(("Couldn't init SDL: %s", SDL_GetError()));
		
		exit(1);
		return;
	}

	SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE);

	// initialized
	Os_inited = 1;

#ifdef WIN32
	// check to see if we're running under msdev
	os_check_debugger();

	// deal with processor affinity
	os_set_process_affinity();
#endif // WIN32

	atexit(os_deinit);

	initializeEventHandling();
}

// set the main window title
void os_set_title( const char * title )
{
	strcpy_s( szWinTitle, title );

	SDL_SetWindowTitle(main_window, szWinTitle);
}

extern void gr_opengl_shutdown();
// call at program end
void os_cleanup()
{
	gr_opengl_shutdown();

#ifndef NDEBUG
	outwnd_close();
#endif
}

// window management -----------------------------------------------------------------

// Returns 1 if app is not the foreground app.
int os_foreground()
{
	return fAppActive;
}

// Returns the handle to the main window
SDL_Window* os_get_window()
{
	return main_window;
}

// Returns the handle to the main window
void os_set_window(SDL_Window* new_handle)
{
	main_window = new_handle;
	fAppActive = true;
}

// process management -----------------------------------------------------------------

// Sleeps for n milliseconds or until app becomes active.
void os_sleep(uint ms)
{
#ifdef __APPLE__
	// ewwww, I hate this!!  SDL_Delay() is causing issues for us though and this
	// basically matches Apple examples of the same thing.  Same as SDL_Delay() but
	// we aren't hitting up the system for anything during the process
	uint then = SDL_GetTicks() + ms;

	while (then > SDL_GetTicks());
#else
	SDL_Delay(ms);
#endif
}

// Used to stop message processing
void os_suspend()
{
	SDL_LockMutex( Os_lock );	
}

// resume message processing
void os_resume()
{
	SDL_UnlockMutex( Os_lock );	
}

// ----------------------------------------------------------------------------------------------------
// OSAPI FORWARD DECLARATIONS
//

// called at shutdown. Makes sure all thread processing terminates.
void os_deinit()
{
	os::eventListeners.clear();

	SDL_DestroyMutex(Os_lock);

	SDL_Quit();
}

void os_poll()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		auto iter = os::eventListeners.find(static_cast<SDL_EventType>(event.type));

		if (iter != os::eventListeners.end())
		{
			for (auto& pair : iter->second)
			{
				if (pair.second.first(event))
				{
					// event got handled
					break;
				}
			}
		}
	}
}

void debug_int3(char *file, int line)
{
	mprintf(("Int3(): From %s at line %d\n", file, line));

	gr_activate(0);

	
#ifndef NDEBUG
	// Try to get a backtrace on linux

#	ifdef WIN32
#		if defined(_MSC_VER) && _MSC_VER >= 1400
	__debugbreak( );
#		elif defined(_MSC_VER)
	_asm int 3;
#		elif defined __GNUC__
	asm("int $3");
#		else
#			error debug_int3: unknown compiler
#		endif
#	elif defined(__linux__)
#	define SIZE 1024
	char **symbols;
	int i, numstrings;
	void *buffer[SIZE];

	numstrings = backtrace(buffer, SIZE);
	symbols = backtrace_symbols(buffer, numstrings);

	if(symbols != NULL)
	{
		for(i = 0; i < numstrings; i++)
		{
			mprintf(("%s\n", symbols[i]));
		}
	}
	free(symbols);
#	endif
#endif

	gr_activate(1);
	// we have to call os_deinit() before abort() so we make sure that SDL gets
	// closed out and we don't lose video/input control
	os_deinit();

	abort();
}

void SCP_Messagebox(MessageBoxType type, const char* message, const char* title) 
{
	int flags = 1;

	switch (type) 
	{
		case MESSAGEBOX_ERROR:
			flags = SDL_MESSAGEBOX_ERROR;
			if (title == NULL)
				title = "Error";
			break;
		case MESSAGEBOX_INFORMATION:
			flags = SDL_MESSAGEBOX_INFORMATION;
			if (title == NULL)
				title = "Information";
			break;
		case MESSAGEBOX_WARNING:
			flags = SDL_MESSAGEBOX_WARNING;
			if (title == NULL)
				title = "Warning";
			break;
		default:
			Int3();
			title = ""; // Remove warning about unitialized variable
			break;
	}

	SDL_ShowSimpleMessageBox(flags, title, message, os_get_window());
}
