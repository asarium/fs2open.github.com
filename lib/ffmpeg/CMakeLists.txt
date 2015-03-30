
# TODO: Add non-windows support with pkg-config

IF(WIN32)
    set(FFMPEG_ROOT_DIR "" CACHE PATH "The root dir of the ffmpeg")

    macro(add_av_lib name libname)
        add_library(${name} SHARED IMPORTED GLOBAL)

        set(include_dir "${FFMPEG_ROOT_DIR}/include/lib${name}")
        set(dll_name "${FFMPEG_ROOT_DIR}/bin/${CMAKE_SHARED_LIBRARY_PREFIX}${libname}${CMAKE_SHARED_LIBRARY_SUFFIX}")
        set(lib_name "${FFMPEG_ROOT_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}${name}${CMAKE_STATIC_LIBRARY_SUFFIX}")

        if (NOT IS_DIRECTORY "${include_dir}")
            message("Couldn't find include directory for ${name} in \"${FFMPEG_ROOT_DIR}\".")
        endif (NOT IS_DIRECTORY "${include_dir}")

        set_target_properties(${name} PROPERTIES
        IMPORTED_LOCATION "${dll_name}"
        IMPORTED_IMPLIB "${lib_name}"
        )

        set_target_properties(${name} PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${FFMPEG_ROOT_DIR}/include"
        )

    	INSTALL(FILES "${dll_name}"
    			DESTINATION ${BINARY_DESTINATION}
    	)

        SET(TARGET_COPY_FILES ${TARGET_COPY_FILES} "${dll_name}" CACHE INTERNAL "" FORCE)
    endmacro(add_av_lib)

    if(IS_DIRECTORY "${FFMPEG_ROOT_DIR}")
        add_av_lib(avcodec avcodec-56)
        add_av_lib(avformat avformat-56)
        add_av_lib(avutil avutil-54)
        add_av_lib(swresample swresample-1)
        add_av_lib(swscale swscale-3)
    else(IS_DIRECTORY "${FFMPEG_ROOT_DIR}")
        message("ffmpeg root directory \"${FFMPEG_ROOT_DIR}\" does not exist")
    endif(IS_DIRECTORY "${FFMPEG_ROOT_DIR}")
ELSE(WIN32)
    # CMake can't check for ffmpeg so we'll just use PkgConfig
    INCLUDE(FindPkgConfig)
    INCLUDE(util)

    macro(add_av_lib name)
        PKG_SEARCH_MODULE(${name} REQUIRED "lib${name}")

        PKG_CONFIG_LIB_RESOLVE(${name} ${name}_LIB)
        ADD_IMPORTED_LIB("${name}" "${${name}_INCLUDE_DIRS}" "${${name}_LIB}" SHARED)
    endmacro(add_av_lib)

    add_av_lib(avcodec)
    add_av_lib(avformat)
    add_av_lib(avutil)
    add_av_lib(swresample)
    add_av_lib(swscale)
ENDIF(WIN32)
