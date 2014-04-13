/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/



#include <time.h>
#include <stdarg.h>

#include "globalincs/globals.h"
#include "parse/generic_log.h"
#include "cfile/cfile.h"



// ----------------------------------------------------------------------------------------------------
// MULTI LOGFILE DEFINES/VARS
//

// max length for a line of the logfile
#define MAX_LOGFILE_LINE_LEN					256

// how often we'll write an update to the logfile (in seconds)
#define MULTI_LOGFILE_UPDATE_TIME			2520			// every 42 minutes
/*
// outfile itself
CFILE *log_file[];
*/

#define MAX_LOGFILES						2

typedef struct logfile {
	char filename[NAME_LENGTH];
	cfile::FileHandle *log_file;
} logfile;

logfile logfiles[MAX_LOGFILES] = {
	// Filename, then the CFILE (which should usually be set to NULL)
	{"multi.log"			,NULL}, 
	{"event.log"			,NULL},
};

// ----------------------------------------------------------------------------------------------------
// LOGFILE FUNCTIONS
//

// initialize the logfile
bool logfile_init(int logfile_type)
{
	if((logfile_type < 0) && (logfile_type >= MAX_LOGFILES)) {
		Warning(LOCATION, "Attempt to write illegal logfile number %d", logfile_type);
		return false;
	}

	// attempt to open the file
	logfiles[logfile_type].log_file = cfile::io::open(logfiles[logfile_type].filename, cfile::MODE_WRITE, cfile::OPEN_NORMAL, cfile::TYPE_DATA);

	if(logfiles[logfile_type].log_file == NULL){
		nprintf(("Network","Error opening %s for writing!!\n",logfiles[logfile_type].filename));
		return false;
	}

	return true;
}

// close down the logfile
void logfile_close(int logfile_type)
{
	// if we have a valid file, write a trailer and close
	if(logfiles[logfile_type].log_file != NULL){

		cfile::io::close(logfiles[logfile_type].log_file);
		logfiles[logfile_type].log_file = NULL;
	}
}

// printf function itself called by the ml_printf macro
void log_printf(int logfile_type, char *format, ...)
{
	char tmp[MAX_LOGFILE_LINE_LEN*4];
	va_list args;

	// if we don't have a valid logfile do nothing
	if(logfiles[logfile_type].log_file == NULL){
		return;
	}
	
	// format the text
	va_start(args, format);
	vsprintf(tmp, format, args);
	va_end(args);
	
	// log the string
	log_string(logfile_type, tmp);
}

// string print function
void log_string(int logfile_type, const char *string, int add_time)
{
	char tmp[MAX_LOGFILE_LINE_LEN*4];
	char time_str[128];
	time_t timer;	

	// if we don't have a valid logfile do nothing
	if(logfiles[logfile_type].log_file == NULL){
		return;
	}

	// if the passed string is NULL, do nothing
	if(string == NULL){
		return;
	}

	// maybe add the time
	if(add_time){
		timer = time(NULL);

		strftime(time_str, 128, "%m/%d %H:%M:%S~   ", localtime(&timer));
		strcpy_s(tmp, time_str);
		strcat_s(tmp, string);
	} else{
		strcpy_s(tmp, string);
	}
	strcat_s(tmp, "\n");

	// now print it to the logfile if necessary	
	cfile::write<const char*>(tmp, logfiles[logfile_type].log_file);
	cfile::io::flush(logfiles[logfile_type].log_file);

#if defined(LOGFILE_ECHO_TO_DEBUG)
	mprintf(("Log file type %d %s",logfile_type, tmp));
#endif
}
