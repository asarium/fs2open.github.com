
set(file_root
    apiTest.hpp
    apiTest.cpp
    ../teststubs.cpp
)

set(file_root_types
    types/vector.cpp
)

set(file_root_lua
)

set(file_root_lua_types
    lua/types/vector_index_tests.lua
    lua/types/vector_operator_tests.lua
)

source_group(""              FILES ${file_root})
source_group("Types"         FILES ${file_root_types})
source_group("Lua"           FILES ${file_root_lua})
source_group("Lua\\Types"    FILES ${file_root_lua_types})

set(file_root
    ${file_root}
    ${file_root_lua}
    ${file_root_lua_types}
    ${file_root_types}
)

# Also build the full list of lua files
set(file_root_lua
    ${file_root_lua}
    ${file_root_lua_types}
)
