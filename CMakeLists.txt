
CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(cmake/util.cmake)

# Set a few policies
set_policy(CMP0051 OLD)
set_policy(CMP0053 NEW)
set_policy(CMP0054 NEW)

SET(FSO_VERSION_MAJOR 3)
SET(FSO_VERSION_MINOR 7)
SET(FSO_VERSION_BUILD 3)
SET(FSO_VERSION_REVISION 0)

SET(FSO_PROJECT_DESCRIPTION "Open source project based on the original FreeSpace 2 source code.")

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin CACHE PATH "Executable output path")
SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin CACHE PATH "Library output path")

# CMAKE_INSTALL_PREFIX is defined but also overwritten by the PROJECT command so we need to set it later
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
	SET(RESET_INSTALL_PREFIX TRUE)
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)

# Reset this variable
SET(TARGET_COPY_FILES "" CACHE INTERNAL "" FORCE)
SET(TARGET_COPY_DIRS "" CACHE INTERNAL "" FORCE)

PROJECT(FS2_Open)

IF(CMAKE_CROSSCOMPILING)
	SET(IMPORT_EXE_DIR "IMPORT_EXE_DIR-NOTFOUND" CACHE FILEPATH "Required for a cross compiling build, point to binary directory of a cmake build for the real OS")
	INCLUDE(${IMPORT_EXE_DIR}/ImportExecutables.cmake)
ENDIF(CMAKE_CROSSCOMPILING)

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/external/rpavlik-cmake-modules")
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/external/cotire")

IF(NOT DEFINED FSO_INSTRUCTION_SET)
	INCLUDE(cpufeatures)
ENDIF(NOT DEFINED FSO_INSTRUCTION_SET)

IF(RESET_INSTALL_PREFIX)
	IF(NOT $ENV{FS2PATH} STREQUAL "")
		IF(NOT IS_DIRECTORY $ENV{FS2PATH})
			MESSAGE(WARNING "The path '$ENV{FS2PATH}' of the environment variable FS2PATH does not point to a directory! Install prefix wasn't set.")
		ELSE(NOT IS_DIRECTORY $ENV{FS2PATH})
			SET(CMAKE_INSTALL_PREFIX "$ENV{FS2PATH}" CACHE FILEPATH "Install path" FORCE)
			FILE(TO_CMAKE_PATH ${CMAKE_INSTALL_PREFIX} CMAKE_INSTALL_PREFIX)
		ENDIF(NOT IS_DIRECTORY $ENV{FS2PATH})
	ELSE(NOT $ENV{FS2PATH} STREQUAL "")
		MESSAGE(STATUS "NO FS2PATH environment variable found, you can define this to point to your freespace install but it is not required.")
	ENDIF(NOT $ENV{FS2PATH} STREQUAL "")
ENDIF(RESET_INSTALL_PREFIX)

IF(DEFINED CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE STRING "Available configurations" FORCE)
ENDIF(DEFINED CMAKE_CONFIGURATION_TYPES)

### Define options and editable variables in the section below:
# This is only needed for single configuration generators so don't annoy others
if(NOT CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Default build configuration used." FORCE)
	message(WARNING "CMAKE_BUILD_TYPE was not specified, defaulting to Release configuration.")
endif(NOT CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)

IF (WIN32)
	OPTION(FSO_USE_SPEECH "Use Windows specific text-to-speach libraries" OFF)

	OPTION(FSO_USE_VOICEREC "Enable voice recognition support" OFF)

	OPTION(FSO_BUILD_FRED2 "Build FRED2 binary" OFF)
ENDIF(WIN32)

OPTION(FSO_BUILD_TOOLS "Build tools related to FSO" OFF)

OPTION(FSO_DEVELOPMENT_MODE "Generate binaries in development mode, only use if you know what you're doing!" OFF)

OPTION(FSO_BUILD_WXFRED2 "Build wxFRED2 binary" OFF)

IF(WIN32)
	# On windows the default should be to always build the included libraries
	SET(FSO_BUILD_INCLUDED_LIBS_DEFAULT ON)
ELSE(WIN32)
	SET(FSO_BUILD_INCLUDED_LIBS_DEFAULT OFF)
ENDIF(WIN32)

OPTION(FSO_BUILD_INCLUDED_LIBS "Build and use the included libraries istead of using the system headers and libraries" ${FSO_BUILD_INCLUDED_LIBS_DEFAULT})

SET(POSSIBLE_INSTUCTION_SETS "" SSE SSE2 AVX)
SET(FSO_INSTRUCTION_SET "" CACHE STRING "The instruction set enhancement to use, possible options are ${POSSIBLE_INSTUCTION_SETS}")

OPTION(FSO_USE_LUAJIT "Use LuaJIT for Lua scripting, needs a working internet connection!" OFF)

OPTION(FSO_USE_OPENALSOFT "Download and build OpenAL Soft instead of using the system libraries" OFF)

SET(FSO_FREESPACE_PATH "${CMAKE_INSTALL_PREFIX}" CACHE FILEPATH "The path of the FreeSpace directory you want to use. Please note that you will have to change CMAKE_INSTALL_PREFIX if you change this at some point.")

SET(FSO_RUN_ARGUMENTS "" CACHE STRING "Additional arguments passed to a generated executable when run with the generated build files.")

LIST(FIND POSSIBLE_INSTUCTION_SETS "${FSO_INSTRUCTION_SET}" SET_INDEX)

IF (SET_INDEX LESS 0)

	MESSAGE(WARNING "Unrecognized instruction set '${FSO_INSTRUCTION_SET}'! Possible values: ${POSSIBLE_INSTUCTION_SETS}. Defaulting to no optionizations.")

	SET(FSO_INSTRUCTION_SET "")
ENDIF(SET_INDEX LESS 0)

OPTION(COTIRE_ENABLE "Enable cotire, this speeds up builds but may cause issues while developing (default = OFF)" OFF)

MARK_AS_ADVANCED(FORCE FSO_CMAKE_DEBUG)
MARK_AS_ADVANCED(FORCE FSO_BUILD_INCLUDED_LIBS)
MARK_AS_ADVANCED(FORCE FSO_USE_OPENALSOFT)
MARK_AS_ADVANCED(FORCE FSO_USE_LUAJIT)
MARK_AS_ADVANCED(FORCE FSO_DEVELOPMENT_MODE)
MARK_AS_ADVANCED(FORCE COTIRE_ENABLE)

IF(COTIRE_ENABLE)
	# Include cotire file from https://github.com/sakra/cotire/
	include(cotire)
ENDIF(COTIRE_ENABLE)

INCLUDE(globals)
INCLUDE(toolchain)
INCLUDE(platforms)

INCLUDE(headers)

SET(GENERATED_SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated_source)

# This includes source code for some tools, either used in the build or also for something else
ADD_SUBDIRECTORY(tools)

ADD_SUBDIRECTORY(lib)

ADD_SUBDIRECTORY(code)

ADD_SUBDIRECTORY(freespace2)

IF(FSO_BUILD_FRED2)
	ADD_SUBDIRECTORY(fred2)
ENDIF(FSO_BUILD_FRED2)

IF(FSO_BUILD_WXFRED2)
	ADD_SUBDIRECTORY(wxfred2)
ENDIF(FSO_BUILD_WXFRED2)

IF(MSVC_USE_RUNTIME_DLL)
	SET(CMAKE_INSTALL_SYSTEM_RUNTIME_DESTINATION "${BINARY_DESTINATION}")

	IF(FSO_BUILD_FRED2)
		SET(CMAKE_INSTALL_MFC_LIBRARIES ON)
	ENDIF(FSO_BUILD_FRED2)

	INCLUDE(InstallRequiredSystemLibraries)
ENDIF(MSVC_USE_RUNTIME_DLL)

include(package)

include(doxygen)
