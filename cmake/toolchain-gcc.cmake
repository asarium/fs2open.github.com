
MESSAGE(STATUS "Doing configuration specific to gcc...")

unset(CMAKE_CXX_FLAGS)
if(DEFINED ENV{CXXFLAGS})
	set(CMAKE_CXX_FLAGS $ENV{CXXFLAGS})
endif(DEFINED ENV{CXXFLAGS})

if(NOT CMAKE_CXX_FLAGS)
	if(CMAKE_SIZEOF_VOID_P EQUAL 4)
		set(CMAKE_CXX_FLAGS "-mtune=generic -mfpmath=sse -msse -msse2 -ansi -pipe")
	elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(CMAKE_CXX_FLAGS "-m64 -mtune=generic -msse -msse2 -ansi -pipe")
	endif()
endif(NOT CMAKE_CXX_FLAGS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -funroll-loops -fsigned-char -Wno-unknown-pragmas")

# Omit "deprecated conversion from string constant to 'char*'" warnings.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-write-strings")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-function")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated -Wno-char-subscripts")

set(CMAKE_CXX_FLAGS_RELEASE "-O2 -Wno-unused-variable -Wno-unused-but-set-variable")

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -Wextra -Wshadow -Wno-unused-parameter")

set(CMAKE_EXE_LINKER_FLAGS "")

set(CMAKE_EXE_LINKER_FLAGS_RELEASE "")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "-g -rdynamic")

IF(${CMAKE_SYSTEM_NAME} MATCHES "SunOS")
	SET(CMAKE_EXE_LINKER_FLAGS "-Wl,-zignore")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "SunOS")
