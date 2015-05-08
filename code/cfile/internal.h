
#ifndef CFILE_INTERNAL_H
#define CFILE_INTERNAL_H
#pragma once

#include "cfile/types.h"

#include <boost/filesystem.hpp>

#include <boost/smart_ptr.hpp>
#include <boost/pool/object_pool.hpp>

#include <VFSPP/merged.hpp>
#include <VFSPP/core.hpp>

namespace cfile
{
	namespace fs = boost::filesystem;

	using namespace vfspp;

	struct FileHandle
	{
		boost::shared_ptr<std::streambuf> buffer;

		std::iostream stream;

		FileEntryPointer entry;

		int mode;

		size_t maxReadLength;
		std::streampos readLengthStart;
		std::streamoff readLengthOffset;

		FileHandle(boost::shared_ptr<std::streambuf> bufferIn, FileEntryPointer entryIn, int modeIn)
			: buffer(bufferIn), stream(bufferIn.get()), entry(entryIn), mode(modeIn), maxReadLength(0)
		{
			Assert(buffer);
			Assert(entryIn);
		}
	};

	extern fs::path rootDir;

	extern fs::path userDir;

	extern boost::shared_ptr<boost::object_pool<FileHandle>> cfilePool;

	extern boost::shared_ptr<merged::MergedFileSystem> fileSystem;

	extern bool inited;

	extern const char* Pathtypes[MAX_PATH_TYPES];

	FileEntryPointer getFileEntry(const SCP_string& path, int mode, DirType dir_type, bool localize);
}

#endif // CFILE_INTERNAL_H
