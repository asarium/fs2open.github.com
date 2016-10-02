
IF(PLATFORM_WINDOWS)
	IF(IS_64BIT)
		# 64-bit
		set(ARCH "x64")
	ELSE()
		# 32-bit
		set(ARCH "x86")
	ENDIF()

	add_library(sdlmain INTERFACE)
	IF(MSVC)
		add_library(sdl SHARED IMPORTED GLOBAL)
		set_target_properties(sdl
			PROPERTIES
				IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/lib/${ARCH}/SDL2.dll"
				IMPORTED_IMPLIB "${CMAKE_CURRENT_SOURCE_DIR}/lib/${ARCH}/SDL2.lib"
		)
		target_link_libraries(sdlmain INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/lib/${ARCH}/SDL2main.lib")
	ELSE(MSVC) #MINGW
		add_library(sdl INTERFACE)
		target_link_libraries(sdl INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/lib/${ARCH}/SDL2.dll")
		target_link_libraries(sdlmain INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/lib/${ARCH}/SDL2main.a")
	ENDIF(MSVC)
	set_target_properties(sdl PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include")

	add_target_copy_files("${CMAKE_CURRENT_SOURCE_DIR}/lib/${ARCH}/SDL2.dll")
	INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/README-SDL.txt"
			DESTINATION ${BINARY_DESTINATION}
	)
elseif(PLATFORM_MAC)
	# We have prebuilt libraries for this platform
	get_prebuilt_path(PREBUILT_PATH)
	find_library(SDL2_LIBRARY SDL2 PATHS "${PREBUILT_PATH}" NO_DEFAULT_PATH)

	add_library(sdl INTERFACE)
	target_link_libraries(sdl INTERFACE "${SDL2_LIBRARY}")
	target_include_directories(sdl INTERFACE "${SDL2_LIBRARY}/Headers")
	
	add_target_copy_files("${SDL2_LIBRARY}")
	INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/README-SDL.txt"
			DESTINATION ${BINARY_DESTINATION}
	)
ELSE()
	# CMake can't check for SDL2 so we'll just use PkgConfig
	find_package(PkgConfig)
	INCLUDE(util)

	PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

	PKG_CONFIG_LIB_RESOLVE(SDL2 SDL2_LIB)
	ADD_IMPORTED_LIB(sdl "${SDL2_INCLUDE_DIRS}" "${SDL2_LIB}")
ENDIF()
