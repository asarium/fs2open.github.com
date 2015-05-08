/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/


#include "globalincs/pstypes.h"

#include "cfile/cfile.h"
#include "cfile/internal.h"

#include "cfile/archives/VPFileSystem.h"
#include "cfile/archives/ZipFileSystem.h"

#include "cmdline/cmdline.h"

#include "osapi/osapi.h"

#include "parse/encrypt.h"

#include <boost/bind.hpp>
#include <boost/ref.hpp>

#include <VFSPP/core.hpp>
#include <VFSPP/merged.hpp>
#include <VFSPP/system.hpp>
#include <VFSPP/7zip.hpp>

namespace cfile
{
	using namespace vfspp;
	using namespace vfspp::merged;
	using namespace vfspp::system;

	using namespace boost;
	namespace fs = boost::filesystem;

	fs::path rootDir;

	fs::path userDir;

	shared_ptr<object_pool<FileHandle>> cfilePool;

	shared_ptr<MergedFileSystem> fileSystem;

	bool inited = false;

	// During cfile_init, verify that Pathtypes[n].index == n for each item
	// Each path must have a valid parent that can be tracable all the way back to the root 
	// so that we can create directories when we need to.
	//
	// Please make sure extensions are all lower-case, or we'll break unix compatibility
	//
	const char* Pathtypes[MAX_PATH_TYPES]  = {
		//Path
		NULL,
		// Root must be index 1!!
		"",
		"data",
		"data/maps",
		"data/text",
		"data/models",
		"data/tables",
		"data/sounds",
		"data/sounds/8b22k",
		"data/sounds/16b11k",
		"data/voice",
		"data/voice/briefing",
		"data/voice/command_briefings",
		"data/voice/debriefing",
		"data/voice/personas",
		"data/voice/special",
		"data/voice/training",
		"data/music",
		"data/movies",
		"data/interface",
		"data/fonts",
		"data/effects",
		"data/hud",
		"data/players",
		"data/players/images",
		"data/players/squads",
		"data/players/single",
		"data/players/single/inferno",
		"data/players/multi",
		"data/players/multi/inferno",
		"data/cache",
		"data/multidata",
		"data/missions",
		"data/config",
		"data/demos",
		"data/cbanims",
		"data/intelanims",
		"data/scripts",
		"data/fiction",
	};

	void addModDirs(SCP_vector<fs::path>& rootDirs, const fs::path& searchPath)
	{
		if (Cmdline_mod) {
			const char* cur_pos;

			// stackable Mod support -- Kazan
			for (cur_pos = Cmdline_mod; *cur_pos != '\0'; cur_pos += (strlen(cur_pos) + 1))
			{
				fs::path modRoot = searchPath / cur_pos;

				if (fs::exists(modRoot))
				{
					rootDirs.push_back(modRoot);
				}
			}
		}
	}

	void searchRootDirectories(SCP_vector<fs::path>& rootDirs, const char* cdromDirStr)
	{
		// First init root directory
		rootDir = fs::current_path();

#ifdef SCP_UNIX
		userDir = detect_home();
		userDir /= Osreg_user_dir;
#endif

		if (!userDir.empty())
		{
			addModDirs(rootDirs, userDir);

			rootDirs.push_back(userDir);
		}

		addModDirs(rootDirs, rootDir);

		rootDirs.push_back(rootDir);

		if (cdromDirStr != NULL)
		{
			rootDirs.push_back(fs::path(cdromDirStr));
		}
	}

	void maybeAddPackSystem(fs::directory_entry entry, SCP_vector<IFileSystem*>& fileSystems)
	{
		if (entry.path().has_extension())
		{
			if (boost::iequals(entry.path().extension().c_str(), ".vp"))
			{
				// Standard VPs
				try
				{
					mprintf(("Found root pack '%s' ... with a checksum of %s\n", 
						entry.path().string().c_str(), checksum::packfile(entry.path().string().c_str()).c_str() ));

					VPFileSystem* system = new VPFileSystem(entry.path(), "");
					fileSystems.push_back(system);
				}
				catch (std::exception& e)
				{
					Error(LOCATION, "Error while reading file %s: %s\n", entry.path().filename().string().c_str(), e.what());
				}
			}
			else if (boost::iequals(entry.path().extension().c_str(), ".vp7"))
			{
				// 7-zip archive
				try
				{
					mprintf(("Found root pack '%s' ... with a checksum of %s\n", 
						entry.path().string().c_str(), checksum::packfile(entry.path().string().c_str()).c_str() ));

					sevenzip::SevenZipFileSystem* system = new sevenzip::SevenZipFileSystem(entry.path());
					fileSystems.push_back(system);
				}
				catch (std::exception& e)
				{
					Error(LOCATION, "Error while reading file %s: %s\n", entry.path().filename().string().c_str(), e.what());
				}
			}
			else if (boost::iequals(entry.path().extension().c_str(), ".vpz"))
			{
				// Zip-archive
				try
				{
					mprintf(("Found root pack '%s' ... with a checksum of %s\n", 
						entry.path().string().c_str(), checksum::packfile(entry.path().string().c_str()).c_str() ));

					ZipFileSystem* system = new ZipFileSystem(entry.path());
					fileSystems.push_back(system);
				}
				catch (std::exception& e)
				{
					Error(LOCATION, "Error while reading file %s: %s\n", entry.path().filename().string().c_str(), e.what());
				}
			}
		}
	}

	void initializeFileSystems(SCP_vector<IFileSystem*>& fileSytems, const SCP_vector<fs::path>& rootDirs)
	{
		bool haveUserDir = !userDir.empty();

		// Initialize physical file systems
		for (const fs::path& path : rootDirs)
		{
			if (!fs::exists(path))
			{
				mprintf(("Was prompted to add root '%s' but it doesn't exist, skipping...", path.string().c_str()));
				continue;
			}

			PhysicalFileSystem* pathSystem = new PhysicalFileSystem(path);

			if (haveUserDir)
			{
				// If we have a user dir then direct all write operations there
				bool isUserDir = fs::equivalent(path, userDir);

				if (isUserDir)
				{
					pathSystem->setAllowedOperations(OP_READ | OP_WRITE | OP_CREATE | OP_DELETE);
				}
				else
				{
					// Only allow read operations anywhere else for now
					pathSystem->setAllowedOperations(OP_READ);
				}
			}
			else
			{
				// If we have no user dir then use the root for writing
				bool isRootDir = fs::equivalent(path, rootDir);

				if (isRootDir)
				{
					pathSystem->setAllowedOperations(OP_READ | OP_WRITE | OP_CREATE | OP_DELETE);
				}
				else
				{
					// Only allow read operations anywhere else for now
					pathSystem->setAllowedOperations(OP_READ);
				}
			}

			fileSytems.push_back(pathSystem);
		}
		
		fs::directory_iterator endIter;
		// Now go through every root and search for pack files
		for (const fs::path& path : rootDirs)
		{
			fs::directory_iterator dirIter(path);

			std::for_each(dirIter, endIter, boost::bind(maybeAddPackSystem, _1, boost::ref(fileSytems)));
		}
	}

	size_t countFiles(IFileSystem* fs)
	{
		std::vector<FileEntryPointer> entries;

		size_t count = 0;

		// Start with 2 here to skip the root path
		for (int i = 2; i < MAX_PATH_TYPES; ++i)
		{
			const char* path = Pathtypes[i];

			FileEntryPointer pointer = fs->getRootEntry()->getChild(path);

			if (pointer)
			{
				entries.clear();
				pointer->listChildren(entries);

				count += std::count_if(entries.begin(), entries.end(), [](FileEntryPointer p) { return p->getType() == vfspp::FILE; });
			}
		}

		return count;
	}

	bool init(const char* cdromDirStr)
	{
		if (inited)
		{
			return true;
		}

		inited = true;

		checksum::crc::init();

		SCP_vector<fs::path> rootDirs;
		searchRootDirectories(rootDirs, cdromDirStr);

		SCP_vector<IFileSystem*> fileSystems;
		initializeFileSystems(fileSystems, rootDirs);

#ifndef NDEBUG
		for (auto fs : fileSystems)
		{
			mprintf(("Searching root %s ... %d files\n", fs->getName().c_str(), countFiles(fs)));
		}
#endif

		// initialize encryption
		encrypt_init();

		// Construct first file system to search for pack files
		fileSystem.reset(new MergedFileSystem());
		fileSystem->setCaseInsensitive(true);

		for (IFileSystem* system : fileSystems)
		{
			fileSystem->addFileSystem(system);
		}

		fileSystem->populateEntries(1);

		cfilePool.reset(new boost::object_pool<FileHandle>());

		return true;
	}

	void shutdown()
	{
		cfilePool.reset();

		fileSystem.reset();
	}
}
