
#include <boost/filesystem.hpp>
#ifdef WIN32
#include <Windows.h>
#endif
#ifdef SCP_UNIX
#include <unistd.h>
#endif

#include "chromium/chromium.h"
#include "chromium/jsapi/jsapi.h"
#include "chromium/ApplicationImpl.h"

#include "mainloop/mainloop.h"
#include "io/timer.h"
#include "mod_table/mod_table.h"
#include "cmdline/cmdline.h"
#include "osapi/osapi.h"

#include "include/cef_app.h"


namespace chromium
{
	namespace fs = boost::filesystem;

	int lastUpdate = 0;

	bool chromiumInited = false;

	CefRefPtr<ApplicationImpl> application;

	SCP_vector<boost::weak_ptr<Browser>> knownBrowsers;

	bool doChromiumWork()
	{
		int now = timer_get_milliseconds();

		if (now - lastUpdate >= 15)
		{
			// Try to limit it to 60 updates per second
			CefDoMessageLoopWork();
			lastUpdate = now;
		}

		return true;
	}

	void init()
	{
		if (!Chromium_enable)
		{
			// Just return here, leaving the chromium system uninited
			return;
		}

		knownBrowsers.clear();
		
		CefSettings settings;
		fs::path base_path, home_path;
		
		// TODO: implement code which works for other platforms (possible using argc and argv
		// to determine the executable path)
		// See http://stackoverflow.com/a/1024937
		// TODO: Parameters in cmdline_fso.cfg are only included on Linux. Windows should also
		// use cmdline_get_args() but I have no idea how to construct an HINSTANCE from our
		// argc and argv... -- ngld
#ifdef WIN32
		CefMainArgs main_args(GetModuleHandle(nullptr));

		WCHAR moduleName[MAX_PATH];
		DWORD result = GetModuleFileNameW(nullptr, moduleName, MAX_PATH);

		if (result == ERROR_INSUFFICIENT_BUFFER)
		{
			mprintf(("Path to executable is too long, errors might occur."));
		}
		
		home_path = fs::path(detect_home()) / "data";
		
#elif SCP_UNIX
		int argc;
		char **argv;

		cmdline_get_args(argc, argv);
		CefMainArgs main_args(argc, argv);
		
		char moduleName[MAX_PATH];
		size_t moduleLen = readlink("/proc/self/exe", moduleName, MAX_PATH);
		
		if (moduleLen == MAX_PATH)
		{
			mprintf(("Path to executable is too long, errors might occur."));
		}
		
		moduleName[moduleLen - 1] = '\0';
		home_path = fs::path(detect_home()) / Osreg_user_dir / "data";
#endif
		base_path = fs::path(moduleName).parent_path();
		
		if (!fs::exists(base_path / CHROMIUM_PROCESS) && !fs::exists(base_path / "chromium" / CHROMIUM_PROCESS))
		{
			Error(LOCATION, "%s is missing! Failed to initialize Chromium!", (base_path / CHROMIUM_PROCESS).string().c_str());
			return;
		}
		
		
		settings.windowless_rendering_enabled = true;
		settings.multi_threaded_message_loop = false;
		settings.remote_debugging_port = 12345;

		CefString(&settings.log_file) = (home_path / "chromium.log").native();
		CefString(&settings.browser_subprocess_path) = (fs::exists(base_path / CHROMIUM_PROCESS) ? base_path / CHROMIUM_PROCESS : base_path / "chromium" / CHROMIUM_PROCESS).native();
		CefString(&settings.resources_dir_path) = (base_path / "chromium").native();
		CefString(&settings.locales_dir_path) = (base_path / "chromium" / "locales").native();
		
		application = new ApplicationImpl();

		CefInitialize(main_args, settings, application.get(), nullptr);

		mainloop::addMainloopFunction(doChromiumWork);

		jsapi::init();

		chromiumInited = true;
	}

	void shutdown()
	{
		if (chromiumInited)
		{
			for (auto& browser : knownBrowsers)
			{
				if (!browser.expired())
				{
					browser.lock()->Close();
				}
			}

			knownBrowsers.clear();

			CefShutdown();
		}
	}

	void addCallback(const CefString& name)
	{
		if (chromiumInited)
		{
			application->AddCallbackName(name);
		}
	}

	void removeCallback(const CefString& name)
	{
		if (chromiumInited)
		{
			application->RemoveCallback(name);
		}
	}

	void addBrowserInstance(boost::weak_ptr<Browser> browser)
	{
		knownBrowsers.push_back(browser);
	}

	bool isInited()
	{
		return chromiumInited;
	}
}
