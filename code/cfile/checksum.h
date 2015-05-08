
#ifndef CFILE_CHECKSUM_H
#define CFILE_CHECKSUM_H
#pragma once

#include "cfile/types.h"

#include "globalincs/pstypes.h"

namespace cfile
{
	namespace checksum
	{
		SCP_string packfile(const SCP_string& path);

		namespace md5
		{
			SCP_string packfile(const SCP_string& path);
		}

		namespace crc
		{
			// get the 2 byte checksum of the passed filename - return 0 if operation failed, 1 if succeeded
			int doShort(const char *filename, ushort *chksum, int max_size = -1, DirType cf_type = TYPE_ANY);

			// get the 2 byte checksum of the passed file - return 0 if operation failed, 1 if succeeded
			// NOTE : preserves current file position
			int doShort(cfile::FileHandle *file, ushort *chksum, int max_size = -1);

			// get the 32 bit CRC checksum of the passed filename - return 0 if operation failed, 1 if succeeded
			int doLong(const char *filename, uint *chksum, int max_size = -1, DirType cf_type = TYPE_ANY);

			// get the 32 bit CRC checksum of the passed file - return 0 if operation failed, 1 if succeeded
			// NOTE : preserves current file position
			int doLong(cfile::FileHandle *file, uint *chksum, int max_size = -1);

			int pack(const char *filename, uint *chk_long, bool full = false);

			// convenient for misc checksumming purposes ------------------------------------------

			// update cur_chksum with the chksum of the new_data of size new_data_size
			ushort doShort(ushort seed, ubyte *buffer, int size);

			// update cur_chksum with the chksum of the new_data of size new_data_size
			uint doLong(uint seed, ubyte *buffer, int size);

			// convenient for misc checksumming purposes ------------------------------------------

			// update cur_chksum with the chksum of the new_data of size new_data_size
			ushort addShort(ushort seed, ubyte *buffer, int size);

			// update cur_chksum with the chksum of the new_data of size new_data_size
			uint addLong(uint seed, ubyte *buffer, int size);

			void init();
		}
	}
}

#endif // CFILE_CHECKSUM_H
