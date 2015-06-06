
# File to execute compiler specific commands

add_library(compiler INTERFACE)

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
