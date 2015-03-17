
add_subdirectory(gtest)

set_target_properties(gtest
	PROPERTIES
		FOLDER "test/gtest"
)
set_target_properties(gtest_main
	PROPERTIES
		FOLDER "test/gtest"
)

add_library(fsoTest INTERFACE)
target_include_directories(fsoTest INTERFACE "${gtest_SOURCE_DIR}/include" "${gtest_SOURCE_DIR}")
target_include_directories(fsoTest INTERFACE "${GENERATED_SOURCE_DIR}/test/")
target_link_libraries(fsoTest INTERFACE gtest_main gtest code)

include(test_util.cmake)

add_subdirectory(src)
