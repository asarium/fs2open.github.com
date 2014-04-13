
#include <algorithm>

#include "globalincs/pstypes.h"
#include "pilotfile/pilotfile_convert.h"
#include "cfile/cfile.h"
#include "playerman/managepilot.h"


pilotfile_convert::pilotfile_convert()
{
	fver = 0;

	m_size_offset = 0;

	cfp = NULL;
	plr = NULL;
	csg = NULL;
}

pilotfile_convert::~pilotfile_convert()
{
	if (cfp) {
		cfile::io::close(cfp);
	}

	if (plr) {
		delete plr;
	}

	if (csg) {
		delete csg;
	}
}

void pilotfile_convert::startSection(Section::id section_id)
{
	Assert( cfp );

	const int zero = 0;

	cfile::write<short>( (ushort)section_id, cfp );

	// to be updated when endSection() is called
	cfile::write<int>(zero, cfp);

	// starting offset, for size of section
	m_size_offset = cfile::io::tell(cfp);
}

void pilotfile_convert::endSection()
{
	Assert( cfp );
	Assert( m_size_offset > 0 );

	size_t cur = cfile::io::tell(cfp);

	Assert( cur >= m_size_offset );

	size_t section_size = cur - m_size_offset;

	if (section_size) {
		// go back to section size in file and write proper value
		cfile::io::seek(cfp, cur - section_size - sizeof(int), cfile::SEEK_MODE_SET);
		cfile::write<int>((int)section_size, cfp);

		// go back to previous location for next section
		cfile::io::seek(cfp, cur, cfile::SEEK_MODE_SET);
	}
}


void convert_pilot_files()
{
	size_t idx, j, i;
	size_t count, inf_count;
	int max_convert, num_converted = 0;
	SCP_vector<SCP_string> existing;
	SCP_vector<SCP_string> old_files;

	// get list of pilots which already exist (new or converted already)
	cfile::listFiles(existing, cfile::TYPE_PLAYERS, "*.plr");

	// Remove file extensions
	std::for_each(existing.begin(), existing.end(), cfile::util::removeExtension<SCP_string>);

	// get list of old pilots which may need converting, starting with inferno pilots

	cfile::listFiles(old_files, cfile::TYPE_SINGLE_PLAYERS_INFERNO, "*.pl2");
	inf_count = old_files.size();

	cfile::listFiles(old_files, cfile::TYPE_SINGLE_PLAYERS, "*.pl2");

	// Remove file extensions
	std::for_each(old_files.begin(), old_files.end(), cfile::util::removeExtension<SCP_string>);

	if ( old_files.empty() ) {
		return;
	}

	// rip out all files which already exist
	i = 0;
	count = old_files.size();
	for (idx = 0; idx < existing.size(); idx++) {
		const char *fname = existing[idx].c_str();

		for (j = 0; j < count; j++) {
			if ( !stricmp(fname, old_files[j].c_str()) ) {
				// NOTE: we just clear the name here to avoid the fragmentation
				//       from resizing the vector
				old_files[j] = "";
				++i;
			}
		}
	}

	// don't convert enough pilots to exceed the pilot limit
	max_convert = MAX_PILOTS - existing.size();

	// if everything is already converted then bail
	// also bail if MAX_PILOTS (or more!) already exist
	if (i == count || max_convert <= 0) {
		return;
	}

	mprintf(("PILOT: Beginning pilot file conversion...\n"));

	// now proceed to convert all of the old files
	count = old_files.size();
	for (idx = 0; idx < count; idx++) {
		if ( old_files[idx].empty() ) {
			continue;
		}

		pilotfile_convert *pcon = new pilotfile_convert;

		bool inferno = (idx < inf_count);

		if ( pcon->plr_convert(old_files[idx].c_str(), inferno) ) {
			SCP_vector<SCP_string> savefiles;

			SCP_string wildcard(old_files[idx]);
			wildcard.append("*.cs2");

			if (inferno)
			{
				cfile::listFiles(savefiles, cfile::TYPE_SINGLE_PLAYERS_INFERNO, wildcard);
			}
			else
			{
				cfile::listFiles(savefiles, cfile::TYPE_SINGLE_PLAYERS, wildcard);
			}

			// Remove file extensions
			std::for_each(savefiles.begin(), savefiles.end(), cfile::util::removeExtension<SCP_string>);

			for (j = 0; j < savefiles.size(); j++) {
				pcon->csg_convert(savefiles[j].c_str(), inferno);
			}

			++num_converted;
		}

		delete pcon;

		if (num_converted >= max_convert) {
			break;
		}
	}

	mprintf(("PILOT: Pilot file conversion complete!\n"));
}
