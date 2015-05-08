
#include "cfile/cfile.h"

#include "cfile/archives/ZipFileSystem.h"

#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>

#include <ctime>

#ifdef WIN32
#include "iowin32.h"
#endif

namespace
{
	time_t makeTimestamp(tm_unz* unzTime)
	{
		tm time;
		memset(&time, 0, sizeof(time));

		time.tm_sec = unzTime->tm_sec;
		time.tm_min = unzTime->tm_min;
		time.tm_hour = unzTime->tm_hour;
		time.tm_mday = unzTime->tm_mday;
		time.tm_mon = unzTime->tm_mon;
		time.tm_year = unzTime->tm_year - 1900;

		return std::mktime(&time);
	}
}

namespace cfile
{

	ZipFileSystem::ZipFileSystem(const boost::filesystem::path& filePathIn)
		: ArchiveFileSystem(filePathIn), zipFile(NULL)
	{
#ifdef WIN32
		// As always, windows needs special treatment...
		zlib_filefunc64_def fileDef;
		fill_win32_filefunc64W(&fileDef);

		zipFile = unzOpen2_64(filePathIn.c_str(), &fileDef);
#else
		zipFile = unzOpen64(filePathIn.c_str());
#endif
		if (!zipFile)
		{
			throw FileSystemException("Failed to open zip file!");
		}

		for (int ret = unzGoToFirstFile(zipFile); ret == UNZ_OK; ret = unzGoToNextFile(zipFile))
		{
			unz_file_info info;

			// Get info to allocate enough string space
			unzGetCurrentFileInfo(zipFile, &info, NULL, 0, NULL, 0, NULL, 0);

			std::string fileName;
			fileName.resize(info.size_filename);

			unzGetCurrentFileInfo(zipFile, &info, &fileName[0], fileName.size(), NULL, 0, NULL, 0);

			boost::to_lower(fileName);

			ZipFileData data;
			data.name = vfspp::util::normalizePath(fileName);
			data.size = info.uncompressed_size;
			data.time = makeTimestamp(&info.tmu_date);
			unzGetFilePos64(zipFile, &data.position);
			
			const char last = fileName[fileName.length() - 1];
			if ((last == '/') || (last == '\\'))
			{
				// This is a directory
				data.type = DIRECTORY;
			}
			else
			{
				data.type = vfspp::FILE;
			}

			addFileData(data.name, data);
		}

		rootEntry.reset(new ZipFileSystemEntry(this, ""));
	}

	ZipFileSystem::~ZipFileSystem()
	{
		if (zipFile)
		{
			unzClose(zipFile);
		}
	}

	boost::shared_array<char> ZipFileSystem::extractEntry(const string_type& path, size_t& arraySize)
	{
		ZipFileData data = getFileData(path);

		if (data.type == UNKNOWN)
		{
			throw FileSystemException("Path is not known!");
		}

		unzGoToFilePos64(zipFile, &data.position);

		unz_file_info fi;
		unzGetCurrentFileInfo(zipFile, &fi, NULL, 0, NULL, 0, NULL, 0);

		if (unzOpenCurrentFile(zipFile) != UNZ_OK)
		{
			throw FileSystemException("Failed to open file!");
		}

		boost::shared_array<char> buffer = boost::shared_array<char>(new char[fi.uncompressed_size]);

		if (unzReadCurrentFile(zipFile, buffer.get(), fi.uncompressed_size) != (int) fi.uncompressed_size)
		{
			boost::shared_array<char>();
		}

		if (unzCloseCurrentFile(zipFile) == UNZ_CRCERROR)
		{
			throw FileSystemException("File checksum was not valid!");
		}

		arraySize = fi.uncompressed_size;

		return buffer;
	}
}
