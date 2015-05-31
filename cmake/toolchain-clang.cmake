# Clang
MESSAGE(STATUS "Doing configuration specific to clang...")

unset(CMAKE_CXX_FLAGS)
if(DEFINED ENV{CXXFLAGS})
	set(CMAKE_CXX_FLAGS $ENV{CXXFLAGS})
endif(DEFINED ENV{CXXFLAGS})

if(NOT CMAKE_CXX_FLAGS)
	if(CMAKE_SIZEOF_VOID_P EQUAL 4)
		set(CMAKE_CXX_FLAGS "-march=i686 -mtune=generic -mfpmath=sse -msse -msse2 -ansi")
	elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(CMAKE_CXX_FLAGS "-m64 -march=x86-64 -mtune=generic -msse -msse2 -ansi")
	endif()
endif(NOT CMAKE_CXX_FLAGS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Omit "argument unused during compilation" when clang is used with ccache.
if(${CMAKE_CXX_COMPILER} MATCHES "ccache")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Qunused-arguments")
endif()
# Omit "conversion from string literal to 'char *' is deprecated" warnings.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-write-strings")
# Omit "unknown pragma ignored" warnings.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unknown-pragmas")
# Omit "... antiquated header ..." warnings. This is caused by clang's usage of GNU/GCC's hash_map.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics")

set(CMAKE_CXX_FLAGS_RELEASE "-O2")

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -Wextra -Wshadow")
