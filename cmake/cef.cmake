
if(NOT DEFINED CEF_BUILD_TYPE)
	# Default to Release
	set(CEF_BUILD_TYPE Release)
endif(NOT DEFINED CEF_BUILD_TYPE)

if(NOT TARGET cef)
	function(CEF_TARGET NAME)
		add_dependencies(${NAME} libcef_dll_wrapper)

		add_custom_command(
			TARGET ${NAME}
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_directory "${CEF_PATH}/Resources" "$<TARGET_FILE_DIR:${NAME}>/chromium"
			COMMENT "Copying CEF resources..."
			VERBATIM
		)

		set(CEF_LIB_NAMES)
		set(LIB_ROOT_PATH "${CEF_PATH}/Release")

		file(GLOB CEF_LIBS "${LIB_ROOT_PATH}/${CMAKE_SHARED_LIBRARY_PREFIX}*${CMAKE_SHARED_LIBRARY_SUFFIX}")
		foreach(filepath ${CEF_LIBS})
			file(RELATIVE_PATH FILE_NAME "${LIB_ROOT_PATH}" "${filepath}")

			# Don't copy the pdf plugin, we don't need it
			if (NOT "${FILE_NAME}" STREQUAL "${CMAKE_SHARED_LIBRARY_PREFIX}pdf${CMAKE_SHARED_LIBRARY_SUFFIX}")
				set(CEF_LIB_NAMES ${CEF_LIB_NAMES} "${FILE_NAME}")
			endif (NOT "${FILE_NAME}" STREQUAL "${CMAKE_SHARED_LIBRARY_PREFIX}pdf${CMAKE_SHARED_LIBRARY_SUFFIX}")
		endforeach(filepath ${CEF_LIBS})

		list(LENGTH CEF_LIB_NAMES CEF_LIBS_SIZE)
		set(i 0)

		foreach(lib IN LISTS CEF_LIB_NAMES)
			math(EXPR i "${i} + 1")
			add_custom_command(
				TARGET ${NAME}
				COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CEF_PATH}/${CEF_BUILD_TYPE}/${lib}" "$<TARGET_FILE_DIR:${NAME}>"
				COMMENT "[${i}/${CEF_LIBS_SIZE}] Copying CEF libraries..."
				VERBATIM
			)
		endforeach(lib IN LISTS CEF_LIBS)

		target_link_libraries(${NAME} PUBLIC cef_dll_wrapper)
	endfunction(CEF_TARGET)

	if(NOT EXISTS ${CEF_PATH}/include)
		message(FATAL_ERROR "The passed CEF_PATH is not valid!")
	endif(NOT EXISTS ${CEF_PATH}/include)

	add_library(cef IMPORTED SHARED GLOBAL)
	add_library(cef_dll_wrapper INTERFACE)

	if(NOT TARGET libcef_dll_wrapper)
		add_subdirectory("${CEF_PATH}/libcef_dll" libcef_dll)

		target_include_directories(libcef_dll_wrapper PUBLIC "${CEF_PATH}")
		set_target_properties(libcef_dll_wrapper
			PROPERTIES
				FOLDER "3rdparty"
		)
	endif(NOT TARGET libcef_dll_wrapper)

	if(WIN32)
		set_target_properties(cef PROPERTIES
			IMPORTED_IMPLIB "${CEF_PATH}/${CEF_BUILD_TYPE}/libcef.lib"
			IMPORTED_LOCATION "${CEF_PATH}/${CEF_BUILD_TYPE}/libcef.dll"
		)
	elseif(UNIX)
		set_target_properties(cef PROPERTIES
			INTERFACE_LINK_LIBRARIES "-Wl,-rpath ."
			IMPORTED_LOCATION "${CEF_PATH}/${CEF_BUILD_TYPE}/libcef.so"
		)
	endif(WIN32)

	target_link_libraries(cef_dll_wrapper INTERFACE cef libcef_dll_wrapper)

	if (UNIX)
		find_package(PkgConfig)

		if(PKG_CONFIG_FOUND)
			pkg_check_modules(GTK gtk+-2.0)
		endif(PKG_CONFIG_FOUND)

		target_include_directories(cef_dll_wrapper INTERFACE ${GTK_INCLUDE_DIRS})
		target_link_libraries(cef_dll_wrapper INTERFACE ${GTK_LIBRARIES})
	endif (UNIX)

	# Define install files
	install(DIRECTORY "${CEF_PATH}/Resources/locales" DESTINATION ${BINARY_DESTINATION}/chromium)
	file(GLOB RESOURCE_FILES "${CEF_PATH}/Resources/*")
	foreach(resource ${RESOURCE_FILES})
		if (NOT IS_DIRECTORY "${resource}")
			install(FILES "${resource}" DESTINATION ${BINARY_DESTINATION}/chromium)
		endif (NOT IS_DIRECTORY "${resource}")
	endforeach(resource)

	set(CEF_LIB_NAMES)
	set(LIB_ROOT_PATH "${CEF_PATH}/${CEF_BUILD_TYPE}")

	file(GLOB CEF_LIBS "${LIB_ROOT_PATH}/${CMAKE_SHARED_LIBRARY_PREFIX}*${CMAKE_SHARED_LIBRARY_SUFFIX}")
	foreach(filepath ${CEF_LIBS})
		file(RELATIVE_PATH FILE_NAME "${LIB_ROOT_PATH}" "${filepath}")

		# Don't copy the pdf plugin, we don't need it
		if (NOT "${FILE_NAME}" STREQUAL "${CMAKE_SHARED_LIBRARY_PREFIX}pdf${CMAKE_SHARED_LIBRARY_SUFFIX}")
			set(CEF_LIB_NAMES ${CEF_LIB_NAMES} "${FILE_NAME}")
		endif (NOT "${FILE_NAME}" STREQUAL "${CMAKE_SHARED_LIBRARY_PREFIX}pdf${CMAKE_SHARED_LIBRARY_SUFFIX}")
	endforeach(filepath ${CEF_LIBS})

	list(LENGTH CEF_LIB_NAMES CEF_LIBS_SIZE)
	set(i 0)

	foreach(lib IN LISTS CEF_LIB_NAMES)
		install(FILES "${LIB_ROOT_PATH}/${lib}" DESTINATION ${BINARY_DESTINATION})
	endforeach(lib IN LISTS CEF_LIBS)
endif(NOT TARGET cef)
