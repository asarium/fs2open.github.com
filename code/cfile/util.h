
#ifndef CFILE_UTIL_H
#define CFILE_UTIL_H
#pragma once

#include "cfile/types.h"

#include "globalincs/pstypes.h"

namespace cfile
{
	namespace legacy
	{
		int read_compressed(void *buf, int elsize, int nelem, FileHandle *cfile);

		char *add_ext(const char *filename, const char *ext);
	}

	namespace util
	{
		void generateVPChecksums();

		template<class String>
		void removeExtension(String& string)
		{
			typename String::size_type dot = string.find_last_of(".");

			if (dot != String::npos)
			{
				string.resize(dot);
			}
		}

#ifdef WIN32
		const char PlatformDirectorySeparator = '\\';
#else
		const char PlatformDirectorySeparator = '/';
#endif
	}
}

#endif // CFILE_UTIL_H
