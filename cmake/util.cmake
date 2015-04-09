
FUNCTION(MAKE_CACHE_INTERNAL VARIABLE)
	SET(${VARIABLE} ${${VARIABLE}} CACHE INTERNAL "Internal cache variable")
ENDFUNCTION(MAKE_CACHE_INTERNAL)

FUNCTION(ADD_IMPORTED_LIB NAME INCLUDES LIBS LIB_TYPE)
	ADD_LIBRARY(${NAME} ${LIB_TYPE} IMPORTED GLOBAL)

	LIST(GET LIBS 0 MAIN_LIB)
	LIST(LENGTH LIBS LIBS_SIZE)

	SET(INTERFACE_LIBS)

	if(${LIBS_SIZE} GREATER 1)
		math(EXPR LIBS_SIZE "${LIBS_SIZE} - 1")
		foreach(i RANGE 1 ${LIBS_SIZE})
			LIST(GET LIBS ${i} LIB)

			SET(INTERFACE_LIBS ${INTERFACE_LIBS} "${LIB}")
		endforeach(i)
	endif(${LIBS_SIZE} GREATER 1)

	set_target_properties(${NAME}
		PROPERTIES
			IMPORTED_LOCATION "${MAIN_LIB}"
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

function(list_target_dependencies _target _out_var)
	set(out_list)
	set(work_libs ${_target})
	list(LENGTH work_libs libs_length)

	while(libs_length GREATER 0)
		list(GET work_libs 0 current)
		list(REMOVE_AT work_libs 0)
		list(APPEND out_list ${current})

		get_target_property(current_libs ${current} INTERFACE_LINK_LIBRARIES)

		if(current_libs)
			foreach(lib ${current_libs})
				if (TARGET ${lib})
					list(APPEND work_libs ${lib})
				endif (TARGET ${lib})
			endforeach(lib)
		endif(current_libs)

		list(LENGTH work_libs libs_length)
	endwhile(libs_length GREATER 0)

	list(REMOVE_DUPLICATES out_list)
	set(${_out_var} ${out_list} PARENT_SCOPE)
endfunction(list_target_dependencies)
