
#include "globalincs/pstypes.h"

#include "cfile/archives/ZipFileSystem.h"
#include "cfile/archives/ZipFileSystemEntry.h"

#include <boost/algorithm/string.hpp>

#include <boost/unordered_map.hpp>

#include <boost/iostreams/concepts.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/device/mapped_file.hpp>

#include <boost/thread/lock_guard.hpp>

namespace cfile
{
	using namespace boost;
	using namespace boost::iostreams;

	template<typename Ch>
	class MemoryBuffer : public boost::iostreams::basic_array<Ch>
	{
	private:
		// We keep this here so the data is deallocated when this object is deleted
		boost::shared_array<Ch> dataPtr;

	public:
		MemoryBuffer(shared_array<Ch> data, size_t n)
			: boost::iostreams::basic_array<Ch>(data.get(), n), dataPtr(data)
		{
		}
	};

	ZipFileSystemEntry::ZipFileSystemEntry(ZipFileSystem* parentSystemIn, const string_type& pathIn)
		: IFileSystemEntry(pathIn), parentSystem(parentSystemIn)
	{
	}

	FileEntryPointer ZipFileSystemEntry::getChild(const string_type& searchPath)
	{
		if (getType() != DIRECTORY)
		{
			throw InvalidOperationException("Entry is no directory!");
		}

		string_type childPath = this->path;
		childPath.append(DirectorySeparatorStr).append(searchPath);
		childPath = vfspp::util::normalizePath(childPath);

		EntryType type = parentSystem->getFileData(childPath).type;

		if (type == UNKNOWN)
		{
			return FileEntryPointer();
		}
		else
		{
			return FileEntryPointer(new ZipFileSystemEntry(parentSystem, childPath));
		}
	}

	size_t ZipFileSystemEntry::numChildren()
	{
		if (getType() != DIRECTORY)
		{
			throw InvalidOperationException("Entry is no directory!");
		}

		size_t num = 0;
		for(const ZipFileData& data : parentSystem->fileData)
		{
			if (boost::algorithm::starts_with(data.name, path))
			{
				// This is a child of this directory, now we need to check if it's in a subdirectory
				size_t pos = data.name.find_last_of('/');

				if (pos == string_type::npos)
				{
					// Couldn't find separator, it's a child if we are the root
					if (path.length() == 0)
					{
						++num;
					}
				}
				else
				{
					if (pos == path.length())
					{
						++num;
					}
				}
			}
		}

		return num;
	}

	void ZipFileSystemEntry::listChildren(std::vector<FileEntryPointer>& outVector)
	{
		if (getType() != DIRECTORY)
		{
			throw InvalidOperationException("Entry is no directory!");
		}

		outVector.clear();

		for(const ZipFileData& data : parentSystem->fileData)
		{
			if (boost::algorithm::starts_with(data.name, path))
			{
				// This is a child of this directory, now we need to check if it's in a subdirectory
				size_t pos = data.name.find_last_of('/');

				if (pos == string_type::npos)
				{
					// Couldn't find separator, it's a child if we are the root
					if (path.length() == 0)
					{
						outVector.push_back(FileEntryPointer(new ZipFileSystemEntry(parentSystem, data.name)));
					}
				}
				else
				{
					if (pos == path.length())
					{
						outVector.push_back(FileEntryPointer(new ZipFileSystemEntry(parentSystem, data.name)));
					}
				}
			}
		}
	}

	EntryType ZipFileSystemEntry::getType() const
	{
		return parentSystem->getFileData(path).type;
	}

	bool ZipFileSystemEntry::deleteChild(const string_type& name)
	{
		throw InvalidOperationException("Zip archives are read only!");
	}

	FileEntryPointer ZipFileSystemEntry::createEntry(EntryType type, const string_type& name)
	{
		throw InvalidOperationException("Zip archives are read only!");
	}

	boost::shared_ptr<std::streambuf> ZipFileSystemEntry::open(int mode)
	{
		using namespace boost::iostreams;
		if (getType() != vfspp::FILE)
		{
			throw InvalidOperationException("Entry is no file!");
		}

		if (mode & MODE_WRITE)
		{
			throw InvalidOperationException("Zip archives are read only!");
		}

		if (mode & MODE_MEMORY_MAPPED)
		{
			throw FileSystemException("Cannot open Zip-entry in memory mapped mode!");
		}

		size_t size;
		shared_array<char> data = parentSystem->extractEntry(path, size);

		return boost::shared_ptr<std::streambuf>(new stream_buffer<MemoryBuffer<char> >(MemoryBuffer<char>(data, size)));
	}

	void ZipFileSystemEntry::rename(const string_type& newPath)
	{
		throw InvalidOperationException("Zip archives are read-only!");
	}

	time_t ZipFileSystemEntry::lastWriteTime()
	{
		return parentSystem->getFileData(path).time;
	}
}
