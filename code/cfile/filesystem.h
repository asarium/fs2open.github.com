
#ifndef CFILE_FILESYSTEM_H
#define CFILE_FILESYSTEM_H
#pragma once

#include "cfile/types.h"

#include "globalincs/pstypes.h"

namespace cfile
{

	/**
	* @brief Gets the root directory of the CFile system
	*
	* @return SCP_string
	*/
	SCP_string getRootDir();

	/**
	* @brief Lists all file names in the specified directory
	*
	* @param names Vector for storing the file names
	* @param pathType The directory type to search in
	* @param filter Glob filter, an empty filter does accept all files. Defaults to "".
	* @param sortMode Specifies the mode for searching. Defaults to SORT_NONE.
	* @param filterFunction Function for filtering files. Defaults to none.
	* @param returnFullPath If set to true, the file names will be full paths. Defaults to false.
	* @return void
	*/
	void listFiles(SCP_vector<SCP_string>& names, DirType pathType, const SCP_string& filter = "", SortMode sortMode = SORT_NONE, ListFilterFunction filterFunction = NULL, bool returnFullPath = false);

	void listFiles(SCP_vector<SCP_string>& names, SCP_string directory, const SCP_string& filter = "", SortMode sortMode = SORT_NONE, ListFilterFunction filterFunction = NULL, bool returnFullPath = false);

	/**
	* @brief Checks if the specified file exists
	*
	* @param path The name or the path of the file to check
	* @param type The directory type of the file. Defaults to TYPE_ANY.
	* @param localize Set to true to check localized files. Defaults to false.
	* @return bool
	*/
	bool exists(const SCP_string& path, DirType type = TYPE_ANY, bool localize = false);

	bool findFile(const SCP_string& name, SCP_string& outName, DirType type = TYPE_ANY, const char** exts = NULL, size_t numExts = 0, size_t* out_extIndex = NULL, bool localize = false);

	bool access(const SCP_string& name, DirType type, int mode);

	bool deleteFile(const SCP_string& path, DirType type = TYPE_ANY, bool localize = false);

	size_t flushDir(DirType type);

	DirType getPathType(const SCP_string& path);

	bool rename(const SCP_string& oldName, const SCP_string& newName, DirType type = TYPE_ANY, bool localize = false);

}

#endif // CFILE_FILESYSTEM_H
