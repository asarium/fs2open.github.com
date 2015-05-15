
MESSAGE(STATUS "Doing configuration specific to gcc...")

unset(CMAKE_CXX_FLAGS)
if(DEFINED ENV{CXXFLAGS})
	set(CMAKE_CXX_FLAGS $ENV{CXXFLAGS})
endif(DEFINED ENV{CXXFLAGS})

if(NOT CMAKE_CXX_FLAGS)
	if(CMAKE_SIZEOF_VOID_P EQUAL 4)
		set(CMAKE_CXX_FLAGS "-march=i686 -mtune=generic -mfpmath=sse -msse -msse2")
	elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(CMAKE_CXX_FLAGS "-m64 -march=x86-64 -mtune=generic -msse -msse2")
	endif()
endif(NOT CMAKE_CXX_FLAGS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -funroll-loops -fsigned-char")

# Omit "deprecated conversion from string constant to 'char*'" warnings.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-write-strings")
# Omit "unused parameter 'foo'" warnings.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter")

set(CMAKE_CXX_FLAGS_RELEASE "-O2")

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -Wextra -Wshadow")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,-O1 -Wl,--as-needed")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-Wl,--strip-all")

IF(${CMAKE_SYSTEM_NAME} MATCHES "SunOS")
	SET(CMAKE_EXE_LINKER_FLAGS "-Wl,-zignore")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "SunOS")
