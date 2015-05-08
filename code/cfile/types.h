
#ifndef CFILE_TYPES_H
#define CFILE_TYPES_H
#pragma once

#include "globalincs/pstypes.h"

namespace cfile
{
	struct FileHandle;

	/**
	* @brief General CFile exception
	*/
	class Exception : public std::exception
	{
	public:
		Exception() : m_excuse("CFILE Exception")
		{
		}

		Exception(const std::string &excuse) : m_excuse(excuse)
		{
		}

		~Exception() throw()
		{
		}

		virtual const char *what() const throw()
		{
			return m_excuse.c_str();
		}

	private:
		std::string m_excuse;
	};

	/**
	* @brief Exception thrown when the maximum read length is exceeded
	*/
	class MaxReadLengthException : public Exception
	{
	public:
		MaxReadLengthException(const std::string &excuse) : Exception(excuse)
		{
		}

		MaxReadLengthException() : Exception("Attempted to read beyond length limit")
		{
		}
	};

	/**
	* @brief Exception thrown when the end of the file is reached
	*
	*/
	class EOFException : public Exception
	{
	public:
		EOFException(const std::string &excuse) : Exception(excuse)
		{
		}

		EOFException() : Exception("End of file has been reached.")
		{
		}
	};

	/**
	* @brief Controls how files are opened
	*
	*/
	enum OpenType
	{
		OPEN_NORMAL = 0,			//!< open file normally
		OPEN_MEMORY_MAPPED = (1 << 0)	//!<	open file as a memory-mapped file
	};

	/**
	* @brief Controls the open mode of a file
	*
	*/
	enum OpenMode
	{
		MODE_READ = 1 << 0, //!< Open the file for reading
		MODE_WRITE = 1 << 1 //!< Open the file for writing
	};

	enum DirType
	{
		TYPE_INVALID = 0,

		TYPE_ROOT = 1,			// Root must be 1!!
		TYPE_DATA = 2,
		TYPE_MAPS = 3,
		TYPE_TEXT = 4,
		TYPE_MODELS = 5,
		TYPE_TABLES = 6,
		TYPE_SOUNDS = 7,
		TYPE_SOUNDS_8B22K = 8,
		TYPE_SOUNDS_16B11K = 9,
		TYPE_VOICE = 10,
		TYPE_VOICE_BRIEFINGS = 11,
		TYPE_VOICE_CMD_BRIEF = 12,
		TYPE_VOICE_DEBRIEFINGS = 13,
		TYPE_VOICE_PERSONAS = 14,
		TYPE_VOICE_SPECIAL = 15,
		TYPE_VOICE_TRAINING = 16,
		TYPE_MUSIC = 17,
		TYPE_MOVIES = 18,
		TYPE_INTERFACE = 19,
		TYPE_FONT = 20,
		TYPE_EFFECTS = 21,
		TYPE_HUD = 22,
		TYPE_PLAYERS = 23,
		TYPE_PLAYER_IMAGES = 24,
		TYPE_SQUAD_IMAGES = 25,
		TYPE_SINGLE_PLAYERS = 26,
		TYPE_SINGLE_PLAYERS_INFERNO = 27,
		TYPE_MULTI_PLAYERS = 28,
		TYPE_MULTI_PLAYERS_INFERNO = 29,
		TYPE_CACHE = 30,
		TYPE_MULTI_CACHE = 31,
		TYPE_MISSIONS = 32,
		TYPE_CONFIG = 33,
		TYPE_DEMOS = 34,
		TYPE_CBANIMS = 35,
		TYPE_INTEL_ANIMS = 36,
		TYPE_SCRIPTS = 37,
		TYPE_FICTION = 38,

		MAX_PATH_TYPES,

		TYPE_ANY = -1,		// Used to check in any directory
	};

	/**
	* @brief Controls the seek origin
	*
	*/
	enum SeekMode
	{
		SEEK_MODE_SET = 0, //!< Seek from the beginning of the file
		SEEK_MODE_CUR = 1, //!< Seek from the current position
		SEEK_MODE_END = 2, //!< Seek from the end of the file
	};

	/**
	* @brief Controls how files should be sorted
	*
	*/
	enum SortMode
	{
		SORT_NONE = 0, //!< Don't sort at all
		SORT_NAME = 1, //!< Sort alphabetically
		SORT_TIME = 2, //!< Sort for time
		SORT_REVERSE = 3, //!< Reverse the direction
	};

	/**
	* @brief Function for filtering files when listing the contents of a directory
	*/
	typedef bool(*ListFilterFunction)(const std::string&);
}
#endif // CFILE_TYPES_H
