
#include "cfile/internal.h"
#include "cfile/io.h"

#include <VFSPP/core.hpp>

#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/device/mapped_file.hpp>

namespace
{
	using namespace vfspp;
	using namespace cfile;

	using namespace boost;

	int toVfsppMode(int mode, OpenType type)
	{
		int outMode = 0;

		if (mode & MODE_READ)
		{
			outMode |= IFileSystemEntry::MODE_READ;
		}

		if (mode & MODE_WRITE)
		{
			outMode |= IFileSystemEntry::MODE_WRITE;
		}

		if (type & OPEN_MEMORY_MAPPED)
		{
			outMode |= IFileSystemEntry::MODE_MEMORY_MAPPED;
		}

		Assertion(outMode != 0, "Invalid open mode specified!");

		return outMode;
	}
}

namespace cfile
{
	namespace io
	{
		FileHandle* open(const SCP_string& file_path, int mode, OpenType type, DirType dir_type, bool localize)
		{
			Assertion(inited, "CFile system has not been inited!");

			Assertion(!file_path.empty(), "Invalid file path given!");
			Assertion(mode != 0, "Invalid mode given!");

			FileEntryPointer fullEntry = getFileEntry(file_path, mode, dir_type, localize);

			if (!fullEntry)
			{
				return NULL;
			}

			try
			{
				boost::shared_ptr<std::streambuf> buffer = fullEntry->open(toVfsppMode(mode, type));

				if (!buffer)
				{
					return NULL;
				}

				FileHandle* handle = cfilePool->construct(buffer, fullEntry, mode);

				Assertion(handle, "Failed to allocate memory for file handle!");

				return handle;
			}
			catch (const FileSystemException& e)
			{
				mprintf(("Failed to open %s: %s\n", file_path.c_str(), e.what()));
			}
			catch (const InvalidOperationException& e)
			{
				mprintf(("Failed to open %s: %s\n", file_path.c_str(), e.what()));
			}

			return NULL;
		}

		bool close(FileHandle* handle)
		{
			Assert(handle);
			Assertion(cfilePool->is_from(handle), "Handle not allocated by the cfile system!");

			handle->stream.flush();
			try
			{
				cfilePool->destroy(handle);
			}
			catch (...)
			{
				// in case the destructor throws, catch and return false
				return false;
			}

			return true;
		}

		std::iostream& getStream(FileHandle* handle)
		{
			Assert(handle != NULL);
			Assertion(handle->maxReadLength == 0, "Trying to use C++ stream with read length restriction is not possible!");

			return handle->stream;
		}

		void setMaxReadLength(FileHandle* handle, size_t size)
		{
			Assert(handle != NULL);
			Assert(handle->mode & MODE_READ);

			handle->maxReadLength = size;
			handle->readLengthOffset = 0;
			handle->readLengthStart = handle->stream.tellg();
		}

		const std::string& getFilePath(FileHandle* handle)
		{
			return handle->entry->getPath();
		}

		bool flush(FileHandle* handle)
		{
			Assert(handle != NULL);

			try
			{
				handle->stream.flush();
			}
			catch (std::exception& e)
			{
				mprintf(("Failed to flush stream: %s", e.what()));
				return false;
			}
			catch (...)
			{
				mprintf(("Failed to flush stream!"));
				return false;
			}

			return true;
		}

		int seek(FileHandle *fp, int offset, cfile::SeekMode where)
		{
			Assert(fp != NULL);

			std::ios::seekdir dir;

			switch (where)
			{
			case SEEK_MODE_CUR:
				dir = std::ios::cur;
				break;
			case SEEK_MODE_END:
				dir = std::ios::end;
				break;
			case SEEK_MODE_SET:
				dir = std::ios::beg;
				break;
			default:
				Int3();
				dir = std::ios::beg;
			}

			// Clear error bits as the following operation can fail if we don't do that
			fp->stream.clear();

			if (fp->mode & MODE_WRITE)
				fp->stream.seekg(offset, dir);

			if (fp->mode & MODE_READ)
				fp->stream.seekp(offset, dir);


			if (!fp->stream.fail())
			{
				return 0;
			}
			else
			{
				return 1;
			}
		}

		int tell(FileHandle* fp)
		{
			Assert(fp != NULL);

			if (fp->mode & MODE_WRITE)
				return static_cast<int>(fp->stream.tellp());
			else if (fp->mode & MODE_READ)
				return static_cast<int>(fp->stream.tellg());
			else
				Int3();

			return -1;
		}

		bool eof(FileHandle* fp)
		{
			Assert(fp != NULL);
			Assert(fp->mode & MODE_READ);

			// Not very elegant but sadly needed
			if (fp->stream.peek() == EOF)
			{
				return true;
			}

			return fp->stream.eof();
		}

		int fileLength(FileHandle* handle)
		{
			int curr = tell(handle);

			seek(handle, 0, SEEK_MODE_END);

			int length = tell(handle);

			seek(handle, curr, SEEK_MODE_SET);

			return length;
		}

		template<>
		char read<char>(FileHandle* handle)
		{
			Assert(handle != NULL);

			char c;

			if (read(&c, sizeof(c), 1, handle) != 1)
				return 0;

			return c;
		}

		template<>
		ubyte read<ubyte>(FileHandle* handle)
		{
			Assert(handle != NULL);

			ubyte c;

			if (read(&c, sizeof(c), 1, handle) != 1)
				return 0;

			return c;
		}

		template<>
		int read<int>(FileHandle* handle)
		{
			Assert(handle != NULL);

			int i;

			if (read(&i, sizeof(i), 1, handle) != 1)
				return 0;

			i = INTEL_INT(i);
			return i;
		}

		template<>
		short read<short>(FileHandle* handle)
		{
			Assert(handle != NULL);

			short s;

			if (read(&s, sizeof(s), 1, handle) != 1)
				return 0;

			s = INTEL_SHORT(s);
			return s;
		}

		template<>
		ushort read<ushort>(FileHandle* handle)
		{
			Assert(handle != NULL);

			ushort s;

			if (read(&s, sizeof(s), 1, handle) != 1)
				return 0;

			s = INTEL_SHORT(s);
			return s;
		}

		template<>
		uint read<uint>(FileHandle* handle)
		{
			Assert(handle != NULL);

			uint i;

			if (read(&i, sizeof(i), 1, handle) != 1)
				return 0;

			i = INTEL_INT(i);
			return i;
		}

		template<>
		float read<float>(FileHandle* handle)
		{
			Assert(handle != NULL);

			float f;

			if (read(&f, sizeof(f), 1, handle) != 1)
				return 0.0f;

			f = INTEL_FLOAT(&f);
			return f;
		}

		template<>
		double read<double>(FileHandle* handle)
		{
			Assert(handle != NULL);

			double f;

			if (read(&f, sizeof(f), 1, handle) != 1)
				return 0.0;

			f = INTEL_FLOAT(&f);
			return f;
		}

		template<>
		vec3d read<vec3d>(FileHandle* handle)
		{
			Assert(handle != NULL);

			vec3d v;

			v.xyz.x = read<float>(handle);
			v.xyz.y = read<float>(handle);
			v.xyz.z = read<float>(handle);

			return v;
		}

		int read(void* buf, int elsize, int nelem, FileHandle* handle)
		{
			Assert(handle != NULL);
			Assert(handle->mode & MODE_READ);

			if (handle->maxReadLength > 0)
			{
				std::streampos diff = handle->stream.tellg() - handle->readLengthStart;

				Assertion(diff >= 0, "Seeked before read length restriction start!");

				if (diff > handle->maxReadLength)
				{
					std::ostringstream os;

					os << "Attempted to read " << (diff - static_cast<std::streampos>(handle->maxReadLength)) << "-byte(s) beyond length limit";

					throw MaxReadLengthException(os.str());
				}
			}

			handle->stream.read(reinterpret_cast<char*>(buf), elsize * nelem);

			return static_cast<int>(handle->stream.gcount()) / elsize;
		}

		void readString(char* buf, int n, FileHandle* handle)
		{
			Assert(handle != NULL);

			char c;

			do {
				c = read<char>(handle);
				if (n > 0)	{
					*buf++ = c;
					n--;
				}
			} while (c != 0);
		}

		bool readLine(char* buf, int n, FileHandle* handle)
		{
			Assert(handle != NULL);
			Assert(buf != NULL);
			Assert(n > 0);

			char * t = buf;
			int i, c;

			for (i = 0; i<n - 1; i++) {
				do {
					char tmp_c;

					int ret = read(&tmp_c, 1, 1, handle);
					if (ret != 1) {
						*buf = 0;
						if (buf > t) {
							return true;
						}
						else {
							return false;
						}
					}
					c = int(tmp_c);
				} while (c == 13);
				*buf++ = char(c);
				if (c == '\n') break;
			}
			*buf++ = 0;

			return true;
		}

		void readStringLen(char* buf, int n, FileHandle* handle)
		{
			Assert(handle != NULL);

			int len;
			len = read<int>(handle);
			Assertion((len < n), "len: %i, n: %i", len, n);
			if (len)
				read(buf, len, 1, handle);

			buf[len] = 0;
		}

		template<>
		bool write<char>(boost::call_traits<char>::param_type val, FileHandle* handle)
		{
			return write(&val, sizeof(char), 1, handle) == 1;
		}

		template<>
		bool write<ubyte>(boost::call_traits<ubyte>::param_type val, FileHandle* handle)
		{
			return write(&val, sizeof(ubyte), 1, handle) == 1;
		}

		template<>
		bool write<short>(boost::call_traits<short>::param_type val, FileHandle* handle)
		{
			short s = INTEL_SHORT(val);
			return write(&s, sizeof(short), 1, handle) == 1;
		}

		template<>
		bool write<ushort>(boost::call_traits<ushort>::param_type val, FileHandle* handle)
		{
			ushort s = INTEL_SHORT(val);
			return write(&s, sizeof(ushort), 1, handle) == 1;
		}

		template<>
		bool write<int>(boost::call_traits<int>::param_type val, FileHandle* handle)
		{
			int i = INTEL_INT(val);
			return write(&i, sizeof(int), 1, handle) == 1;
		}

		template<>
		bool write<uint>(boost::call_traits<uint>::param_type val, FileHandle* handle)
		{
			uint i = INTEL_INT(val);
			return write(&i, sizeof(uint), 1, handle) == 1;
		}

		template<>
		bool write<float>(boost::call_traits<float>::param_type val, FileHandle* handle)
		{
			float i = INTEL_SHORT(val);
			return write(&i, sizeof(float), 1, handle) == 1;
		}

		template<>
		bool write<char const *>(boost::call_traits<const char*>::param_type buf, cfile::FileHandle* handle)
		{
			Assert(handle != NULL);

			if ((!buf) || (buf && !buf[0])) {
				return write<char>(0, handle);
			}
			int len = strlen(buf);
			if (!write(buf, len, 1, handle)){
				return 0;
			}
			return write<char>(0, handle);
		}

		int write(const void* buf, int elsize, int nelem, FileHandle* handle)
		{
			Assert(handle != NULL);
			Assert(handle->mode & MODE_WRITE);

			handle->stream.write(reinterpret_cast<const char*>(buf), elsize * nelem);

			// Assume everything was written
			return nelem;
		}

		void writeStringLen(const char* buf, FileHandle* handle)
		{
			int len = strlen(buf);

			write<int>(len, handle);

			if (len)
			{
				write(buf, len, 1, handle);
			}
		}

		void* returndata(FileHandle* handle)
		{
			// This relies heavily on the implementation in VFSPP!!!
			using namespace boost::iostreams;

			typedef stream_buffer<mapped_file> mapped_buffer;

			shared_ptr<mapped_buffer> mappedBuffer = dynamic_pointer_cast<mapped_buffer>(handle->buffer);
			Assert(mappedBuffer);

			return (*mappedBuffer)->data();
		}
	}
}
