
function(generateTestFiles name listVar outVar)
    SET(TEST_OUT_FILES)
    FOREACH(file ${${listVar}})
        get_filename_component(FILE_NAME "${file}" NAME)

        set(INPUT_NAME "${CMAKE_CURRENT_SOURCE_DIR}/${file}")
    	SET(OUTPUT "${GENERATED_SOURCE_DIR}/test/${name}/${file}.h")

    	# For some reason this is needed...
    	GET_FILENAME_COMPONENT(DIRECTORY_PATH ${OUTPUT} PATH)
    	FILE(MAKE_DIRECTORY ${DIRECTORY_PATH})

    	STRING(REPLACE "-" "_" FILE_NAME ${FILE_NAME})
    	STRING(REPLACE "." "_" FILE_NAME ${FILE_NAME})
    	STRING(REPLACE "#" "_" FILE_NAME ${FILE_NAME})

    	ADD_CUSTOM_COMMAND(
    		OUTPUT ${OUTPUT}
    		COMMAND embedfile -text "${INPUT_NAME}" "${OUTPUT}" "test_${FILE_NAME}"
    		DEPENDS ${INPUT_NAME}
    		COMMENT "Generating string file for ${INPUT_NAME}"
    		)

    	LIST(APPEND TEST_OUT_FILES ${OUTPUT})
    ENDFOREACH(file)

    SOURCE_GROUP("Generated Files\\Test Files" FILES ${TEST_OUT_FILES})

    set(${outVar} ${TEST_OUT_FILES} PARENT_SCOPE)
endfunction(generateTestFiles)
