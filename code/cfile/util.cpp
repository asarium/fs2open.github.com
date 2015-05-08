
#include "cfile/util.h"
#include "cfile/io.h"

namespace cfile
{
	namespace legacy
	{
		int read_compressed(void *buf, int elsize, int nelem, FileHandle *cfile)
		{
			char *out = (char *)buf;

			while (1)	{

				ubyte count;

				if (io::read(&count, 1, 1, cfile) != 1)	{
					break;
				}

				int run_span = count & 0x80;
				count &= (~0x80);
				count++;

				if (count > 0)	{
					if (run_span)	{
						// RLE'd data
						ubyte c;
						if (io::read(&c, 1, 1, cfile) != 1)	{
							break;
						}
						memset(out, c, count);
					}
					else {
						if (io::read(out, 1, count, cfile) != count)	{
							break;
						}
					}
					out += count;
					if (out >= (char *)buf + (elsize*nelem))	{
						break;
					}
				}
				else {
					break;
				}
			}

			return (out - (char *)buf) / elsize;
		}

		char *add_ext(const char *filename, const char *ext)
		{
			int flen, elen;
			static char path[MAX_PATH_LEN];

			flen = strlen(filename);
			elen = strlen(ext);
			Assert(flen < MAX_PATH_LEN);
			strcpy_s(path, filename);
			if ((flen < 4) || stricmp(path + flen - elen, ext)) {
				Assert(flen + elen < MAX_PATH_LEN);
				strcat_s(path, ext);
			}

			return path;
		}

	}

	namespace util
	{
		void generateVPChecksums()
		{
		}
	}
}
