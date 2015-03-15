
set(LUA_FOUND TRUE)
set(LUA_LIBRARIES ${LUA_LIBS})

add_subdirectory(luabind)

add_library(luabind_interface INTERFACE)

set_target_properties(luabind PROPERTIES FOLDER "3rdparty")

target_link_libraries(luabind_interface INTERFACE boost)
target_link_libraries(luabind_interface INTERFACE ${LUA_LIBS})
target_link_libraries(luabind_interface INTERFACE luabind)

target_include_directories(luabind_interface INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/luabind")

set(LUABIND_LIBS luabind_interface CACHE INTERNAL "" FORCE)
