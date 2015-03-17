
add_subdirectory(gtest)

set_target_properties(gtest
	PROPERTIES
		FOLDER "test/gtest"
)
set_target_properties(gtest_main
	PROPERTIES
		FOLDER "test/gtest"
)

add_subdirectory(src)
