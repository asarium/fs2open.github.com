
include(source_groups.cmake)

generateTestFiles("api" file_root_lua LUA_FILES)

add_executable(apiTests ${file_root} ${LUA_FILES})

target_link_libraries(apiTests PUBLIC fsoTest)
target_include_directories(apiTests PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

set_target_properties(apiTests
	PROPERTIES
		FOLDER "test"
)
