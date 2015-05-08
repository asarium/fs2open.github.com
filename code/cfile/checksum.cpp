
#include <sstream>
#include <iomanip>

#include "cfile/checksum.h"
#include "cfile/io.h"

#include "cmdline/cmdline.h"

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include <md5.h>

namespace cfile
{
	namespace fs = boost::filesystem;

	namespace checksum
	{
		SCP_string packfile(const SCP_string& path)
		{
			if (Cmdline_use_md5)
			{
				return md5::packfile(path);
			}
			else
			{
				uint chksum = 0;
				cfile::checksum::crc::pack(path.c_str(), &chksum);

				SCP_stringstream stream;
				stream << "0x" << std::setw(8) << std::hex << chksum;

				return stream.str();
			}
		}

		namespace md5
		{
			SCP_string packfile(const SCP_string& path)
			{
				fs::path filePath(path.c_str());

				fs::ifstream stream(filePath, std::ios::binary);

				if (!stream.good())
				{
					mprintf(("Failed to open file for checksum generation: %s\n", path.c_str()));
					return "";
				}

				MD5 md5;

				const size_t BUFFER_SIZE = 4096;
				char buffer[BUFFER_SIZE];

				std::streamsize readCount;

				do
				{
					stream.read(buffer, BUFFER_SIZE);

					if (stream.fail() && !stream.eof())
					{
						mprintf(("Failed to read from file for checksum generation: %s\n", path.c_str()));
						return "";
					}

					readCount = stream.gcount();

					if (readCount > 0)
					{
						md5.update(buffer, static_cast<MD5::size_type>(readCount));
					}

				} while (readCount > 0 && !stream.eof());

				md5.finalize();
				return md5.hexdigest().c_str();
			}
		}

		namespace crc
		{
			// 16 and 32 bit checksum stuff ----------------------------------------------------------

			// CRC code for mission validation.  given to us by Kevin Bentley on 7/20/98.   Some sort of
			// checksumming code that he wrote a while ago.  
#define CRC32_POLYNOMIAL					0xEDB88320
			uint CRCTable[256];

#define CF_CHKSUM_SAMPLE_SIZE				512

			// update cur_chksum with the chksum of the new_data of size new_data_size
			ushort addShort(ushort seed, ubyte *buffer, int size)
			{
				ubyte *ptr = buffer;
				uint sum1, sum2;

				sum1 = sum2 = (int)(seed);

				while (size--)	{
					sum1 += *ptr++;
					if (sum1 >= 255) sum1 -= 255;
					sum2 += sum1;
				}
				sum2 %= 255;

				return (ushort)((sum1 << 8) + sum2);
			}

			// update cur_chksum with the chksum of the new_data of size new_data_size
			uint addLong(uint seed, ubyte *buffer, int size)
			{
				uint crc;
				ubyte *p;

				p = buffer;
				crc = seed;

				while (size--)
					crc = (crc >> 8) ^ CRCTable[(crc ^ *p++) & 0xff];

				return crc;
			}

			void init()
			{
				int i, j;
				uint crc;

				for (i = 0; i < 256; i++) {
					crc = i;

					for (j = 8; j > 0; j--) {
						if (crc & 1)
							crc = (crc >> 1) ^ CRC32_POLYNOMIAL;
						else
							crc >>= 1;
					}

					CRCTable[i] = crc;
				}
			}

			// single function convenient to use for both short and long checksums
			// NOTE : only one of chk_short or chk_long must be non-NULL (indicating which checksum to perform)
			int doSum(FileHandle *cfile, ushort *chk_short, uint *chk_long, int max_size)
			{
				ubyte cf_buffer[CF_CHKSUM_SAMPLE_SIZE];
				int is_long;
				int cf_len = 0;
				int cf_total;
				int read_size;

				// determine whether we're doing a short or long checksum
				is_long = 0;
				if (chk_short){
					Assert(!chk_long);
					*chk_short = 0;
				}
				else {
					Assert(chk_long);
					is_long = 1;
					*chk_long = 0;
				}

				// if max_size is -1, set it to be the size of the file
				if (max_size < 0){
					io::seek(cfile, 0, SEEK_MODE_SET);
					max_size = io::fileLength(cfile);
				}

				cf_total = 0;
				do {
					// determine how much we want to read
					if ((max_size - cf_total) >= CF_CHKSUM_SAMPLE_SIZE){
						read_size = CF_CHKSUM_SAMPLE_SIZE;
					}
					else {
						read_size = max_size - cf_total;
					}

					// read in some buffer
					cf_len = io::read(cf_buffer, 1, read_size, cfile);

					// total we've read so far
					cf_total += cf_len;

					// add the checksum
					if (cf_len > 0){
						// do the proper short or long checksum
						if (is_long){
							*chk_long = addLong(*chk_long, cf_buffer, cf_len);
						}
						else {
							*chk_short = addShort(*chk_short, cf_buffer, cf_len);
						}
					}
				} while ((cf_len > 0) && (cf_total < max_size));

				return 1;
			}

			// get the chksum of a pack file (VP)
			int pack(const char *filename, uint *chk_long, bool full)
			{
				const int safe_size = 2097152; // 2 Meg
				const int header_offset = 32;  // skip 32bytes for header (header is currently smaller than this though)

				ubyte cf_buffer[CF_CHKSUM_SAMPLE_SIZE];
				int cf_len = 0;
				int cf_total;
				int read_size;
				int max_size;

				if (chk_long == NULL) {
					Int3();
					return 0;
				}

				std::FILE *fp = fopen(filename, "rb");

				if (fp == NULL) {
					*chk_long = 0;
					return 0;
				}

				*chk_long = 0;

				// get the max size
				fseek(fp, 0, SEEK_END);
				max_size = ftell(fp);

				// maybe do a chksum of the entire file
				if (full) {
					fseek(fp, 0, SEEK_SET);
				}
				// othewise it's only a partial check
				else {
					CLAMP(max_size, 0, safe_size);

					Assertion(max_size > header_offset,
						"max_size (%d) > header_offset in packfile %s", max_size, filename);
					max_size -= header_offset;

					fseek(fp, -(max_size), SEEK_END);
				}

				cf_total = 0;

				do {
					// determine how much we want to read
					if ((max_size - cf_total) >= CF_CHKSUM_SAMPLE_SIZE)
						read_size = CF_CHKSUM_SAMPLE_SIZE;
					else
						read_size = max_size - cf_total;

					// read in some buffer
					cf_len = fread(cf_buffer, 1, read_size, fp);

					// total we've read so far
					cf_total += cf_len;

					// add the checksum
					if (cf_len > 0)
						*chk_long = addLong((*chk_long), cf_buffer, cf_len);
				} while ((cf_len > 0) && (cf_total < max_size));

				fclose(fp);

				return 1;
			}
			// get the 2 byte checksum of the passed filename - return 0 if operation failed, 1 if succeeded
			int doShort(const char *filename, ushort *chksum, int max_size, DirType cf_type)
			{
				int ret_val;
				FileHandle *cfile = NULL;

				// zero the checksum
				*chksum = 0;

				// attempt to open the file
				cfile = io::open(filename, MODE_READ, OPEN_NORMAL, cf_type);
				if (cfile == NULL){
					return 0;
				}

				// call the overloaded cf_chksum function()
				ret_val = doSum(cfile, chksum, NULL, max_size);

				// close the file down
				io::close(cfile);
				cfile = NULL;

				// return the result
				return ret_val;
			}

			// get the 2 byte checksum of the passed file - return 0 if operation failed, 1 if succeeded
			// NOTE : preserves current file position
			int doShort(FileHandle *file, ushort *chksum, int max_size)
			{
				int ret_code;
				int start_pos;

				// Returns current position of file.
				start_pos = io::tell(file);
				if (start_pos == -1){
					return 0;
				}

				// move to the beginning of the file
				if (io::seek(file, 0, SEEK_MODE_SET)){
					return 0;
				}

				ret_code = doSum(file, chksum, NULL, max_size);
				// move back to the start position
				io::seek(file, start_pos, SEEK_MODE_SET);

				return ret_code;
			}

			// get the 32 bit CRC checksum of the passed filename - return 0 if operation failed, 1 if succeeded
			int doLong(const char *filename, uint *chksum, int max_size, DirType cf_type)
			{
				int ret_val;
				FileHandle *cfile = NULL;

				// zero the checksum
				*chksum = 0;

				// attempt to open the file
				cfile = io::open(filename, MODE_READ, OPEN_NORMAL, cf_type);
				if (cfile == NULL){
					return 0;
				}

				// call the overloaded cf_chksum function()
				ret_val = doSum(cfile, NULL, chksum, max_size);

				// close the file down
				io::close(cfile);
				cfile = NULL;

				// return the result
				return ret_val;
			}

			// get the 32 bit CRC checksum of the passed file - return 0 if operation failed, 1 if succeeded
			// NOTE : preserves current file position
			int doLong(FileHandle *file, uint *chksum, int max_size)
			{
				int ret_code;
				int start_pos;

				// Returns current position of file.
				start_pos = io::tell(file);
				if (start_pos == -1){
					return 0;
				}

				// move to the beginning of the file
				if (io::seek(file, 0, SEEK_MODE_SET)){
					return 0;
				}
				ret_code = doSum(file, NULL, chksum, max_size);
				// move back to the start position
				io::seek(file, start_pos, SEEK_MODE_SET);

				return ret_code;
			}
		}
	}
}
