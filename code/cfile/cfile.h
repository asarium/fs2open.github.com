/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/ 



#ifndef __CFILE_H__
#define __CFILE_H__

#include "globalincs/pstypes.h"

#include "cfile/checksum.h"
#include "cfile/filesystem.h"
#include "cfile/io.h"
#include "cfile/types.h"
#include "cfile/util.h"

namespace cfile
{
	/**
	 * @brief Initializes the CFile system
	 * 
	 * @param cdromDir Directory of the CD-ROM Defaults to NULL.
	 * @return bool
	 */
	bool init(const char* cdromDir = NULL);

	/**
	 * @brief Frees resources of the CFile system
	 * 
	 * @return void
	 */
	void shutdown();
}


#endif	/* __CFILE_H__ */
