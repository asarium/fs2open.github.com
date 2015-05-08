
#ifndef ZIPFILESYSTEM_H
#define ZIPFILESYSTEM_H

#include <VFSPP/util.hpp>

#include <unzip.h>

#include <boost/filesystem/path.hpp>

#include <boost/unordered_map.hpp>

#include <boost/thread/mutex.hpp>

#include <boost/scoped_ptr.hpp>
#include <boost/shared_array.hpp>

#include "cfile/archives/ZipFileSystemEntry.h"

namespace cfile
{
	using namespace vfspp;

	class ZipFileData
	{
	public:
		std::string name;
		EntryType type;

		unz64_file_pos position;
		size_t size;
		time_t time;

		ZipFileData() : name(), type(UNKNOWN), size(0), time(0)
		{
			memset(&position, 0, sizeof(position));
		}
	};

	class ZipFileSystem : public vfspp::util::ArchiveFileSystem<ZipFileData>
	{
	private:
		unzFile zipFile;

		boost::filesystem::path filePath;

		boost::mutex fileMutex;

		boost::scoped_ptr<ZipFileSystemEntry> rootEntry;

		boost::shared_array<char> extractEntry(const string_type& path, size_t& arraySize);

		friend class ZipFileSystemEntry;

	public:
		ZipFileSystem(const boost::filesystem::path& filePath);

		virtual ~ZipFileSystem();

		virtual ZipFileSystemEntry* getRootEntry() { return rootEntry.get(); }

		virtual int supportedOperations() const { return vfspp::OP_READ; }
	};
}

#endif // ZIPFILESYSTEM_H
