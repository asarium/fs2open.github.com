
FUNCTION(MAKE_CACHE_INTERNAL VARIABLE)
	SET(${VARIABLE} ${${VARIABLE}} CACHE INTERNAL "Internal cache variable")
ENDFUNCTION(MAKE_CACHE_INTERNAL)

FUNCTION(ADD_IMPORTED_LIB NAME INCLUDES LIBS LIB_TYPE)
	ADD_LIBRARY(${NAME} ${LIB_TYPE} IMPORTED GLOBAL)

	LIST(GET LIBS 0 MAIN_LIB)
	LIST(LENGTH LIBS LIBS_SIZE)

	SET(INTERFACE_LIBS)

	if(${LIBS_SIZE} GREATER 0)
		LIST(GET LIBS 0 MAIN_LIB)

		set_target_properties(${NAME}
			PROPERTIES
				IMPORTED_LOCATION "${MAIN_LIB}"
		)

		math(EXPR LIBS_SIZE "${LIBS_SIZE} - 1")

		if(${LIBS_SIZE} GREATER 0)
			foreach(i RANGE 1 ${LIBS_SIZE})
				LIST(GET LIBS ${i} LIB)

				SET(INTERFACE_LIBS ${INTERFACE_LIBS} "${LIB}")
			endforeach(i)
		endif(${LIBS_SIZE} GREATER 0)
	endif(${LIBS_SIZE} GREATER 0)

	set_target_properties(${NAME}
		PROPERTIES
			INTERFACE_INCLUDE_DIRECTORIES "${INCLUDES}"
			IMPORTED_LINK_INTERFACE_LIBRARIES "${INTERFACE_LIBS}"
	)
ENDFUNCTION(ADD_IMPORTED_LIB)

MACRO(PKG_CONFIG_LIB_RESOLVE NAME OUTVAR)
	SET(${OUTVAR} "")
	foreach(lib ${${NAME}_LIBRARIES})
		find_library(${lib}_LIBRARY
					NAMES ${lib}
					HINTS ${${NAME}_LIBDIR} ${${NAME}_LIBRARY_DIRS}
		)

		if (NOT ${${lib}_LIBRARY} MATCHES ".*NOTFOUND.*")
			SET(${OUTVAR} ${${OUTVAR}} ${${lib}_LIBRARY})
		endif (NOT ${${lib}_LIBRARY} MATCHES ".*NOTFOUND.*")
	endforeach(lib)
ENDMACRO(PKG_CONFIG_LIB_RESOLVE)

# Copy from http://cmake.3232098.n2.nabble.com/RFC-cmake-analog-to-AC-SEARCH-LIBS-td7585423.html
INCLUDE (CheckFunctionExists)
INCLUDE (CheckLibraryExists)

MACRO (CMAKE_SEARCH_LIBS v_func v_lib func)
    CHECK_FUNCTION_EXISTS (${func} ${v_func})
    IF (NOT ${v_func})
        FOREACH (lib ${ARGN})
            CHECK_LIBRARY_EXISTS (${lib} ${func} "" "HAVE_${func}_IN_${lib}")
            IF ("HAVE_${func}_IN_${lib}")
                SET (${v_func} TRUE)
                SET (${v_lib} "${lib}" CACHE INTERNAL "Library providing ${func}")
                BREAK()
            ENDIF ("HAVE_${func}_IN_${lib}")
        ENDFOREACH (lib)
    ENDIF (NOT ${v_func})
ENDMACRO (CMAKE_SEARCH_LIBS)
# End copy

FUNCTION(EP_CHECK_FILE_EXISTS FILE OUTVAR TARGET NAME COMMAND WORKING_DIR)
	string (REPLACE ";" " " COMMAND_STR "${COMMAND}")
	IF(WIN32)
		# Do something special for windows...
		SET(COMMAND "cmd /C \"${COMMAND_STR}\"")
	ELSE(WIN32)
		SET(COMMAND "${COMMAND_STR}")
	ENDIF(WIN32)

	FILE(WRITE "${CMAKE_CURRENT_BINARY_DIR}/${TARGET}/${NAME}" "
IF(EXISTS \"${CMAKE_CURRENT_BINARY_DIR}/${TARGET}/${FILE}\")
	MESSAGE(\"'${CMAKE_CURRENT_BINARY_DIR}/${TARGET}/${FILE}' already exists, nothing to be done.\")
ELSE(EXISTS \"${CMAKE_CURRENT_BINARY_DIR}/${TARGET}/${FILE}\")
	execute_process(COMMAND ${COMMAND} WORKING_DIRECTORY \"${CMAKE_CURRENT_BINARY_DIR}/${TARGET}/${WORKING_DIR}\")
ENDIF(EXISTS \"${CMAKE_CURRENT_BINARY_DIR}/${TARGET}/${FILE}\")
")

	SET(${OUTVAR} "${CMAKE_COMMAND}" -P ${CMAKE_CURRENT_BINARY_DIR}/${TARGET}/${NAME} PARENT_SCOPE)
ENDFUNCTION(EP_CHECK_FILE_EXISTS)

MACRO(COPY_FILES_TO_TARGET _target)
	FOREACH(file IN LISTS TARGET_COPY_FILES)
		ADD_CUSTOM_COMMAND(
			TARGET ${_target} POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different "${file}"  "$<TARGET_FILE_DIR:${_target}>"
			COMMENT "copying '${file}'..."
		)
	ENDFOREACH(file)
ENDMACRO(COPY_FILES_TO_TARGET)

macro(set_policy policy value)
	if (POLICY ${policy})
		cmake_policy(SET ${policy} ${value})
	endif ()
endmacro(set_policy)

macro(configure_cotire target)
	IF(COTIRE_ENABLE)
		# Disable unity build as it doesn't work well for us
		set_target_properties(${target} PROPERTIES COTIRE_ADD_UNITY_BUILD FALSE)

		# add ignored paths for the precompiled header here
		set_target_properties(code PROPERTIES COTIRE_PREFIX_HEADER_IGNORE_PATH
			"${CMAKE_SOURCE_DIR};${CMAKE_BINARY_DIR}")

		IF(DEFINED CMAKE_CONFIGURATION_TYPES)
			cotire(${target} CONFIGURATIONS ${CMAKE_CONFIGURATION_TYPES})
		ELSE(DEFINED CMAKE_CONFIGURATION_TYPES)
			cotire(${target})
		ENDIF(DEFINED CMAKE_CONFIGURATION_TYPES)
	ENDIF(COTIRE_ENABLE)
endmacro(configure_cotire)

macro(_clear_old_libraries_state)
	set(is_debug FALSE)
	set(is_optimized FALSE)
endmacro(_clear_old_libraries_state)

function(CONVERT_OLD_LIBRARIES)
	_clear_old_libraries_state()
	set(out_list)
	foreach(lib ${ARGV})
		if ("${lib}" STREQUAL "debug")
			_clear_old_libraries_state()
			set(is_debug TRUE)
		elseif("${lib}" STREQUAL "optimized")
			_clear_old_libraries_state()
			set(is_optimized TRUE)
		elseif("${lib}" STREQUAL "general")
			_clear_old_libraries_state()
		else("${lib}" STREQUAL "debug")
			# Expecting normal library
			if(is_debug)
				list(APPEND out_list "$<$<CONFIG:Debug>:${lib}>")
			elseif(is_optimized)
				list(APPEND out_list "$<$<CONFIG:Release>:${lib}>")
			else(is_debug)
				list(APPEND out_list "${lib}")
			endif(is_debug)
		endif("${lib}" STREQUAL "debug")
	endforeach(lib)

	set(CONVERTED_LIBRARIES ${out_list} PARENT_SCOPE)
endfunction(CONVERT_OLD_LIBRARIES)
