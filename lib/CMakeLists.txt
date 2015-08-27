
INCLUDE(util)

include(opengl.cmake)

IF(APPLE)
	ADD_SUBDIRECTORY(mac)
ENDIF(APPLE)

ADD_SUBDIRECTORY(libjpeg)

ADD_SUBDIRECTORY(zlib)

ADD_SUBDIRECTORY(libpng)

ADD_SUBDIRECTORY(lua)

ADD_SUBDIRECTORY(oggvorbis)

ADD_SUBDIRECTORY(openal)

ADD_SUBDIRECTORY(minizip)

ADD_SUBDIRECTORY(libsdl)

ADD_SUBDIRECTORY(md5)

IF (USE_SPEECH)
	ADD_SUBDIRECTORY(speech)
ENDIF(USE_SPEECH)

# These are only required for the web-ui which is non-Windows
IF(UNIX)
	ADD_SUBDIRECTORY(jansson)

	ADD_SUBDIRECTORY(mongoose)
ENDIF(UNIX)

include(vfspp.cmake)

IF(MSVC60 OR MSVC70)
	INCLUDE(stlport.cmake)
ENDIF(MSVC60 OR MSVC70)

include(boost.cmake)
