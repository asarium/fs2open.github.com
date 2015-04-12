
set(file_root
    apiTest.hpp
    apiTest.cpp
    ../teststubs.cpp
)

set(file_root_types
    types/vector.cpp
)

set(file_root_libs
    libs/base.cpp
)

source_group(""                      FILES ${file_root})
source_group("Types"                 FILES ${file_root_types})
source_group("Libs"                  FILES ${file_root_libs})

set(file_root
    ${file_root}
    ${file_root_types}
    ${file_root_libs}
)

set(file_root_lua
)

set(file_root_lua_types
)

set(file_root_lua_types_vector
    lua/types/vector/vector_index_tests.lua
    lua/types/vector/vector_operator_tests.lua
)

set(file_root_lua_libs
)

set(file_root_lua_libs_base
    lua/libs/base/base_getFrametime.lua
    lua/libs/base/base_GameEvents.lua
)

set(file_root_lua
    ${file_root_lua}
    ${file_root_lua_types}
    ${file_root_lua_types_vector}
    ${file_root_lua_libs}
    ${file_root_lua_libs_base}
)
