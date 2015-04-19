
SET(DEF_OUT_FILES)
FOREACH(file ${file_root_def_files})
	set(INPUT_NAME "${CMAKE_CURRENT_SOURCE_DIR}/${file}")
	SET(OUTPUT "${GENERATED_SOURCE_DIR}/code/${file}.h")

	# For some reason this is needed...
	GET_FILENAME_COMPONENT(DIRECTORY_PATH ${OUTPUT} PATH)
	FILE(MAKE_DIRECTORY ${DIRECTORY_PATH})

	get_filename_component(FILENAME ${file} NAME)

	STRING(REPLACE "-" "_" FILENAME ${FILENAME})
	STRING(REPLACE "." "_" FILENAME ${FILENAME})
	STRING(REPLACE "#" "_" FILENAME ${FILENAME})

	ADD_CUSTOM_COMMAND(
		OUTPUT ${OUTPUT}
		COMMAND embedfile -text "${INPUT_NAME}" "${OUTPUT}" "Default_${FILENAME}"
		DEPENDS ${INPUT_NAME}
		COMMENT "Generating string file for ${INPUT_NAME}"
		)

	LIST(APPEND DEF_OUT_FILES ${OUTPUT})
ENDFOREACH(file ${file_root_def_files})

SOURCE_GROUP("Generated Files\\Default Files" FILES ${DEF_OUT_FILES})
