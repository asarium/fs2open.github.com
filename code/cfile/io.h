
#ifndef CFILE_IO_H
#define CFILE_IO_H
#pragma once

#include "cfile/types.h"

#include "globalincs/pstypes.h"

#include <boost/call_traits.hpp>

namespace cfile
{
	namespace io
	{
		FileHandle* open(const SCP_string& file_path, int mode = MODE_READ, OpenType type = OPEN_NORMAL, DirType dir_type = TYPE_ANY, bool localize = false);

		bool close(FileHandle* handle);

		std::iostream& getStream(FileHandle* handle);

		void setMaxReadLength(FileHandle* handle, size_t size);

		const std::string& getFilePath(FileHandle* handle);

		bool flush(FileHandle* handle);

		int seek(FileHandle *fp, int offset, cfile::SeekMode where);

		int tell(FileHandle* fp);

		bool eof(FileHandle* fp);

		int fileLength(FileHandle* handle);

		template<class T>
		T read(FileHandle* handle);

		int read(void* buf, int elsize, int nelem, FileHandle* handle);

		void readString(char* buf, int n, FileHandle* handle);

		bool readLine(char* buf, int n, FileHandle* handle);

		/**
		* @brief Read a fixed length string that is not null-terminated, with the length stored in file
		*
		* @param buf Pre-allocated array to store string
		* @param n Size of pre-allocated array
		* @param file File to read from
		*
		* @note Appends NULL character to string (buf)
		*/
		void readStringLen(char* buf, int n, FileHandle* file);

		template<class T>
		bool write(typename boost::call_traits<T>::param_type val, FileHandle* handle);

		int write(const void* buf, int elsize, int nelem, FileHandle* handle);

		void writeStringLen(const char* buf, FileHandle* handle);

		void* returndata(FileHandle* handle);
	}
}

#endif // CFILE_IO_H
