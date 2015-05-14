
SET(DEF_OUT_FILES)

set(INCLUDE_LIST)
set(ARRAY_ELEMENTS)

FOREACH(file ${file_root_def_files})
	set(INPUT_NAME "${CMAKE_CURRENT_SOURCE_DIR}/${file}")
	SET(OUTPUT "${GENERATED_SOURCE_DIR}/code/${file}")

	# For some reason this is needed...
	GET_FILENAME_COMPONENT(DIRECTORY_PATH ${OUTPUT} PATH)
	FILE(MAKE_DIRECTORY ${DIRECTORY_PATH})

	get_filename_component(FILENAME ${file} NAME)

	string(MAKE_C_IDENTIFIER "${FILENAME}" FIELD_NAME)

	set(HEADER_FILE "${OUTPUT}.h")
	set(SOURCE_FILE "${OUTPUT}.cpp")

	set(ALL_OUTPUTS "${HEADER_FILE}" "${SOURCE_FILE}")
	set(FIELD_NAME "Default_${FIELD_NAME}")

	set(INCLUDE_LIST "${INCLUDE_LIST}\n#include \"${file}.h\"")
	set(ARRAY_ELEMENTS "${ARRAY_ELEMENTS}\n\t{ \"${FILENAME}\" , ${FIELD_NAME} },")

	ADD_CUSTOM_COMMAND(
		OUTPUT ${ALL_OUTPUTS}
		COMMAND embedfile -text "${INPUT_NAME}" "${OUTPUT}" "${FIELD_NAME}"
		DEPENDS ${INPUT_NAME}
		COMMENT "Generating string file for ${INPUT_NAME}"
		)

	LIST(APPEND DEF_OUT_FILES ${ALL_OUTPUTS})
ENDFOREACH(file ${file_root_def_files})

configure_file("generated_def_files.h.in" "${GENERATED_SOURCE_DIR}/code/globalincs/generated_def_files.h")
SOURCE_GROUP("Generated Files\\Default Files" FILES ${DEF_OUT_FILES})
