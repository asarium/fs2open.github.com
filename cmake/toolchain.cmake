
# File to execute compiler specific commands

SET(COMPILER_INCLUDES "" CACHE INTERNAL "Compiler specific includes")
SET(COMPILER_LBRARIES "" CACHE INTERNAL "Compiler specific libraries")

ADD_DEFINITIONS(-DNO_CD_CHECK)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	include(toolchain-gcc)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	include(toolchain-msvc)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	include(toolchain-clang)
ELSE("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	MESSAGE(STATUS "No special handling for this compiler present, good luck!")

	IF (NOT FSO_INSTRUCTION_SET STREQUAL "")
		MESSAGE(WARNING "This compiler does not support a special instruction set!")

		SET(FSO_INSTRUCTION_SET "")
	ENDIF(NOT FSO_INSTRUCTION_SET STREQUAL "")
ENDIF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
