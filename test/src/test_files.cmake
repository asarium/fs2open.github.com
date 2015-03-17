
SET(TEST_OUT_FILES)
FOREACH(file ${file_root_api_lua})
    get_filename_component(FILE_NAME "${file}" NAME)
    get_filename_component(DIRECTORY_NAME "${file}" DIRECTORY)

    message("${FILE_NAME}")
    message("${DIRECTORY_NAME}")

    set(INPUT_NAME "${CMAKE_CURRENT_SOURCE_DIR}/${file}")
	SET(OUTPUT "${GENERATED_SOURCE_DIR}/test/${DIRECTORY_NAME}/${FILE_NAME}.h")

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
ENDFOREACH(file ${file_root_def_files})

SOURCE_GROUP("Generated Files\\Test Files" FILES ${TEST_OUT_FILES})
