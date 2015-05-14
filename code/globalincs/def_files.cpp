/*
 * Def_Files.cpp
 *
 * You may not sell or otherwise commercially exploit the source or things you
 * create based on the source.
 */




#include <string.h>
#include "globalincs/pstypes.h"

#include "globalincs/generated_def_files.h"

const char *defaults_get_file(char *filename)
{
	for (auto& def_file : Default_files)
	{
		if (!stricmp(def_file.filename, filename))
		{
			return def_file.contents;
		}
	}

	//WMC - This is really bad, because it means we have a default table missing.
	Error(LOCATION, "Default table '%s' missing from executable - contact a coder.", filename);
	return NULL;
}
