
IF(NOT FSO_BUILD_INCLUDED_LIBS AND UNIX)
	find_package(PkgConfig REQUIRED)
	pkg_check_modules(JANSSON jansson>=2.2)

	IF(JANSSON_FOUND)
		INCLUDE(util)
		PKG_CONFIG_LIB_RESOLVE(JANSSON JANSSON_LIBS)

		ADD_IMPORTED_LIB(jansson "${JANSSON_INCLUDEDIR}" "${JANSSON_LIBS}" SHARED)

		SET(JANSSON_LIBS jansson CACHE INTERNAL "jansson library" FORCE)
	ENDIF(JANSSON_FOUND)
ENDIF(NOT FSO_BUILD_INCLUDED_LIBS AND UNIX)

IF(FSO_BUILD_INCLUDED_LIBS OR NOT JANSSON_FOUND)
	MESSAGE(STATUS "Building jansson from source...")
	SET(JANSSON_SOURCES
		dump.c
		error.c
		hashtable.c
		hashtable_seed.c
		load.c
		memory.c
		pack_unpack.c
		strbuffer.c
		strconv.c
		utf.c
		value.c
		hashtable.h
		jansson.h
		jansson_config.h
		jansson_private.h
		strbuffer.h
		utf.h)

	ADD_LIBRARY(jansson STATIC ${JANSSON_SOURCES})

	INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

	set_target_properties(jansson
		PROPERTIES
			COMPILE_DEFINITIONS _CRT_SECURE_NO_WARNINGS
			INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}
	)

	set_target_properties(jansson
		PROPERTIES
			FOLDER "3rdparty"
	)

	IF(MSVC)
		set_target_properties(jansson
			PROPERTIES
				STATIC_LIBRARY_FLAGS "/LTCG"
		)
	ENDIF(MSVC)

	SET(JANSSON_LIBS jansson CACHE INTERNAL "jansson library")
ENDIF(FSO_BUILD_INCLUDED_LIBS OR NOT JANSSON_FOUND)
