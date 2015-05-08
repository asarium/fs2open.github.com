
#include "cfile/internal.h"
#include "cfile/filesystem.h"

#include "localization/localize.h"

#include <boost/filesystem.hpp>

// sigh...
#undef strcpy_s
#undef strcat_s

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>


#define strcpy_s( ... ) scp_strcpy_s( __FILE__, __LINE__, __VA_ARGS__ )
#define strcat_s( ... ) scp_strcat_s( __FILE__, __LINE__, __VA_ARGS__ )

#include <boost/bind.hpp>

namespace cfile
{
	namespace fs = boost::filesystem;

	SCP_string getRootDir()
	{
		std::string str = rootDir.string();

		return SCP_string(str.begin(), str.end());
	}

	bool access(const SCP_string& file, cfile::DirType type, int mode)
	{
		fs::path workPath(rootDir);
		workPath /= Pathtypes[type];
		workPath /= std::string(file.begin(), file.end());

		fs::file_status fileStatus = fs::status(workPath);

		return fileStatus.permissions() == mode;
	}

	inline bool dirTypeValid(DirType type)
	{
		return type > TYPE_INVALID && type < MAX_PATH_TYPES;
	}

	FileEntryPointer getEntry(const SCP_string& path, int mode, bool localize)
	{
		SCP_string realPath = path;

		if (localize)
		{
			lcl_add_dir_to_path_with_filename(realPath);
		}

		FileEntryPointer entry = fileSystem->getRootEntry()->getChild(realPath.c_str());

		if (entry && entry->getType() == DIRECTORY)
		{
			return FileEntryPointer();
		}
		else
		{
			if (!entry && mode & MODE_WRITE)
			{
				entry = fileSystem->getRootEntry()->createEntry(vfspp::FILE, realPath.c_str());
			}

			return entry;
		}
	}

	FileEntryPointer getFileEntry(const SCP_string& path, int mode, DirType dir_type, bool localize)
	{
		if (path.find(DirectorySeparatorChar) != SCP_string::npos)
		{
			// We already have a path
			return getEntry(path, mode, localize);
		}

		if (dir_type == TYPE_ANY)
		{
			SCP_string searchPath;

			FileEntryPointer entry;
			// Start at 1 because 0 is the invalid entry
			for (int i = 1; i < MAX_PATH_TYPES; ++i)
			{
				searchPath.assign(Pathtypes[i]);
				searchPath.append(DirectorySeparatorStr);
				searchPath.append(path);

				entry = getEntry(searchPath, mode, localize);

				// Break once we have found a valid entry
				if (entry)
					break;
			}

			return entry;
		}
		else
		{
			Assert(dirTypeValid(dir_type));

			SCP_stringstream stream;

			stream << Pathtypes[dir_type] << DirectorySeparatorChar << path;

			return getEntry(stream.str(), mode, localize);
		}
	}

	FileEntryPointer getParent(const FileEntryPointer& child)
	{
		Assertion(child, "Invalid child pointer given!");

		std::string path = child->getPath();

		size_t slash = path.find_last_of(DirectorySeparatorChar);

		if (slash == std::string::npos)
		{
			return FileEntryPointer();
		}
		else
		{
			return fileSystem->getRootEntry()->getChild(path.substr(0, slash));
		}
	}

	struct NameSorter
	{
		bool operator()(const FileEntryPointer& entryA, const FileEntryPointer& entryB) const
		{
			return entryA->getPath() < entryB->getPath();
		}
	};

	struct TimeSorter
	{
		bool operator()(const FileEntryPointer& entryA, const FileEntryPointer& entryB) const
		{
			return entryA->lastWriteTime() < entryB->lastWriteTime();
		}
	};

	void sortEntryVector(std::vector<FileEntryPointer>& children, SortMode mode)
	{
		switch (mode)
		{
		case SORT_NAME:
			std::sort(children.begin(), children.end(), NameSorter());
			break;
		case SORT_TIME:
			std::sort(children.begin(), children.end(), TimeSorter());
			break;
		case SORT_REVERSE:
			std::sort(children.begin(), children.end(), NameSorter());
			std::reverse(children.begin(), children.end());
			break;
		default:
			Error(LOCATION, "Invalid sort mode! Get a coder!");
		}
	}

	SCP_string getEntryFileName(FileEntryPointer& entry)
	{
		SCP_string out;

		const std::string& path = entry->getPath();

		size_t slash = path.find_last_of(DirectorySeparatorChar);

		if (slash == std::string::npos)
		{
			out.assign(path.begin(), path.end());
		}
		else
		{
			out.assign(path.begin() + slash + 1, path.end());
		}

		return out;
	}

	SCP_string getEntryPath(FileEntryPointer& entry)
	{
		const std::string& path = entry->getPath();

		return SCP_string(path.begin(), path.end());
	}

	bool shouldRemoveFull(FileEntryPointer& entryPointer, const boost::regex& wildcardMatcher, ListFilterFunction filterFunc)
	{
		const string_type& path = entryPointer->getPath();

		// as string::npos is (size_t)-1, using + 1 will make it overflow to 0
		size_t begin = path.find_last_of(DirectorySeparatorStr) + 1;

		bool keep = boost::regex_match(path.begin() + begin, path.end(), wildcardMatcher);

		if (keep && filterFunc != NULL)
		{
			keep = filterFunc(path.substr(begin));
		}

		return !keep;
	}

	bool shouldRemoveFunc(FileEntryPointer& entryPointer, ListFilterFunction filterFunc)
	{
		const string_type& path = entryPointer->getPath();

		// as string::npos is (size_t)-1, using + 1 will make it overflow to 0
		size_t begin = path.find_last_of(DirectorySeparatorStr) + 1;

		return filterFunc(path.substr(begin));
	}

	void filterFiles(std::vector<FileEntryPointer>& children, const SCP_string& filter, ListFilterFunction filterFunc)
	{
		if (!filter.empty())
		{
			// RegExp magic to escape otherwise invalid characters
			const boost::regex esc("([\\^\\.\\$\\|\\(\\)\\[\\]\\*\\+\\?\\/\\\\])");
			const char* replacement = "\\\\\\1";
			std::string filterResult = boost::regex_replace(std::string(filter.begin(), filter.end()), esc,
				replacement, boost::match_default | boost::format_sed);

			// We also escaped our wildcards so we need to restore those
			boost::replace_all(filterResult, "\\*", ".*");
			boost::replace_all(filterResult, "\\?", ".");

			boost::regex wildcardMatcher(filterResult);

			children.erase(std::remove_if(children.begin(), children.end(),
				boost::bind(shouldRemoveFull, _1, boost::cref(wildcardMatcher), filterFunc)), children.end());
		}
		else if (filterFunc != NULL)
		{
			children.erase(std::remove_if(children.begin(), children.end(), boost::bind(shouldRemoveFunc, _1, filterFunc)), children.end());
		}
	}

	void listFiles(SCP_vector<SCP_string>& names, DirType pathType, const SCP_string& filter, SortMode sortMode,
		ListFilterFunction filterFunc, bool returnFullPath)
	{
		Assert(dirTypeValid(pathType));

		listFiles(names, Pathtypes[pathType], filter, sortMode, filterFunc, returnFullPath);
	}

	void listFiles(SCP_vector<SCP_string>& names, SCP_string directory, const SCP_string& filter, SortMode sortMode,
		ListFilterFunction filterFunction, bool returnFullPath)
	{
		names.clear();

		FileEntryPointer parentDir = fileSystem->getRootEntry()->getChild(directory.c_str());

		if (!parentDir)
		{
			// Directory not present, no children to be listed...
			return;
		}

		std::vector<FileEntryPointer> children;

		parentDir->listChildren(children);

		filterFiles(children, filter, filterFunction);

		if (sortMode != SORT_NONE)
		{
			sortEntryVector(children, sortMode);
		}

		names.resize(children.size());

		if (returnFullPath)
		{
			std::transform(children.begin(), children.end(), names.begin(), getEntryPath);
		}
		else
		{
			std::transform(children.begin(), children.end(), names.begin(), getEntryFileName);
		}
	}


	bool deleteFile(const SCP_string& path, DirType type, bool localize)
	{
		FileEntryPointer entry = getFileEntry(path, MODE_READ, type, localize);

		if (entry)
		{
			return fileSystem->getRootEntry()->deleteChild(entry->getPath());
		}
		else
		{
			return true;
		}
	}

	size_t flushDir(DirType type)
	{
		Assert(dirTypeValid(type));

		FileEntryPointer entry = fileSystem->getRootEntry()->getChild(Pathtypes[type]);

		if (!entry)
		{
			return 0;
		}

		IFileSystemEntry *root = fileSystem->getRootEntry();

		std::vector<FileEntryPointer> children;
		entry->listChildren(children);

		size_t num = 0;

		std::vector<FileEntryPointer>::iterator iter;
		for (iter = children.begin(); iter != children.end(); ++iter)
		{
			if ((*iter)->getType() == vfspp::FILE)
			{
				if (root->deleteChild((*iter)->getPath()))
				{
					++num;
				}
			}
		}

		return num;
	}

	DirType getPathType(const SCP_string& path)
	{
		SCP_string lowerPath = boost::to_lower_copy(path);

		int type = std::distance(Pathtypes, std::find(Pathtypes, Pathtypes + MAX_PATH_TYPES, lowerPath.c_str()));

		if (type == MAX_PATH_TYPES)
		{
			return TYPE_INVALID;
		}
		else
		{
			return static_cast<DirType>(type);
		}
	}

	bool rename(const SCP_string& oldName, const SCP_string& newName, DirType type, bool localize)
	{
		Assert(dirTypeValid(type));

		FileEntryPointer entry = getFileEntry(oldName, MODE_READ, type, localize);

		try
		{
			entry->rename(std::string(Pathtypes[type]).append(DirectorySeparatorStr).append(newName.begin(), newName.end()));

			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	bool findFile(const SCP_string& name, SCP_string& outName, DirType type, const char** exts, size_t numExts, size_t* out_extIndex, bool localize)
	{
		if (exts == NULL)
		{
			FileEntryPointer entry = getFileEntry(name, MODE_READ, type, localize);

			if (out_extIndex)
				*out_extIndex = (size_t)-1; // Intentional overflow

			if (entry)
			{
				outName.assign(entry->getPath().c_str());

				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			SCP_string correctName(name);

			size_t dot = correctName.find_last_of(".");

			if (dot != SCP_string::npos)
			{
				// We may only strip the extension if it is longer than 1 character
				if (correctName.size() - dot > 2)
				{
					correctName.resize(dot);
				}
			}

			SCP_string workString;

			for (size_t i = 0; i < numExts; ++i)
			{
				Assertion(strlen(exts[i]) > 3, "It is assumed that any extension is at least 3 characters long, get a coder!");

				workString.assign(correctName);
				workString.append(exts[i]);

				FileEntryPointer entry = getFileEntry(workString, MODE_READ, type, localize);

				if (entry)
				{
					if (out_extIndex)
						*out_extIndex = i;

					outName.assign(entry->getPath().begin(), entry->getPath().end());


					return true;
				}
			}

			if (out_extIndex)
				*out_extIndex = (size_t)-1; // Intentional overflow

			// We haven't found anything...
			return false;
		}
	}

	bool exists(const SCP_string& path, DirType type, bool localize)
	{
		return (bool)getFileEntry(path, MODE_READ, type, localize);
	}

}
