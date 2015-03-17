
include(source_groups.cmake)

include(test_files.cmake)

add_executable(gtests ${file_root} ${TEST_OUT_FILES})
target_link_libraries(gtests PUBLIC gtest_main gtest code)

target_include_directories(gtests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(gtests PUBLIC ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set_target_properties(gtests
	PROPERTIES
		FOLDER "test"
)
