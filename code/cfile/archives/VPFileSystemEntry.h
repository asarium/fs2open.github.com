
#ifndef VPFILESYSTEMENTRY_H
#define VPFILESYSTEMENTRY_H

#include "VFSPP/core.hpp"

namespace cfile
{
	class VPFileSystem;

	class VPFileData;

	using namespace vfspp;

	class VPFileSystemEntry : public IFileSystemEntry
	{
	public:
		VPFileSystemEntry(VPFileSystem* parentSystem, const string_type& pathIn);

		virtual ~VPFileSystemEntry() {}

		virtual FileEntryPointer getChild(const string_type& path);

		virtual size_t numChildren();

		virtual void listChildren(std::vector<FileEntryPointer>& outVector);

		virtual boost::shared_ptr<std::streambuf> open(int mode = MODE_READ);

		virtual EntryType getType() const;

		virtual bool deleteChild(const string_type& name);

		virtual FileEntryPointer createEntry(EntryType type, const string_type& name);

		virtual void rename(const string_type& newPath);

		virtual time_t lastWriteTime();

	private:
		VPFileSystem* parentSystem;
	};
}

#endif // VPFILESYSTEMENTRY_H
