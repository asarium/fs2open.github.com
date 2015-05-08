
#ifndef VPFILESYSTEM_H
#define VPFILESYSTEM_H

#include <fstream>

#include "VFSPP/util.hpp"

#include "globalincs/pstypes.h"
#include "cfile/archives/VPFileSystemEntry.h"

#include <boost/unordered_map.hpp>

#include <boost/scoped_ptr.hpp>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include <boost/thread/mutex.hpp>

namespace cfile
{
	using namespace vfspp;

	class VPFileData
	{
	public:
		std::string name;
		EntryType type;

		size_t offset;
		size_t size;
		time_t time;

		VPFileData() : name(), type(UNKNOWN), offset(0), size(0), time(0)
		{}
	};

	class VPFileSystem : public vfspp::util::ArchiveFileSystem<VPFileData>
	{
	private:
		std::string rootPath;
		boost::filesystem::path filePath;

		boost::filesystem::ifstream vpStream;

		boost::scoped_ptr<VPFileSystemEntry> rootEntry;

		boost::mutex streamMutex;

		friend class VPFileSystemEntry;

	public:
		VPFileSystem(const boost::filesystem::path& filePath, const std::string& rootPath);

		virtual ~VPFileSystem();

		virtual VPFileSystemEntry* getRootEntry() { return rootEntry.get(); }

		virtual int supportedOperations() const { return vfspp::OP_READ; }
	};
}

#endif // VPFILESYSTEM_H
