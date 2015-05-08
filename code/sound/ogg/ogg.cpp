

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Mmsystem.h>
#endif

#define NEED_STRHDL		// for STRHTL struct in audiostr.h

#include "cfile/cfile.h"
#include "sound/ogg/ogg.h"
#include "sound/audiostr.h"


int ogg_inited = 0;
ov_callbacks cfile_callbacks;

//Encapsulation funcs to please the almighty ov_callbacks struct
size_t ogg_cfread(void *buf, size_t elsize, size_t elnem, void* cfile)
{
	return cfile::io::read(buf, elsize, elnem, (cfile::FileHandle*)cfile);
}

int ogg_cfseek(void* cfile, ogg_int64_t offset, int where)
{
	// cfile::SeekMode is the same as C seek mode
	return cfile::io::seek((cfile::FileHandle*)cfile, (int) offset, static_cast<cfile::SeekMode>(where));
}

int ogg_cfclose(void* cfile)
{
	// we don't close here so that it's safe to do it ourselves
	return 0;
}

long ogg_cftell(void* cfile)
{
	return cfile::io::tell((cfile::FileHandle*) cfile);
}

int OGG_init()
{
	//Setup the cfile_callbacks stucts
	cfile_callbacks.read_func = ogg_cfread;
	cfile_callbacks.seek_func = ogg_cfseek;
	cfile_callbacks.close_func = ogg_cfclose;
	cfile_callbacks.tell_func = ogg_cftell;

	return 0;
}
