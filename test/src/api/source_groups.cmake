
set(file_root
    apiTest.hpp
    apiTest.cpp
    ../teststubs.cpp
)

set(file_root_types
    types/vector.cpp
)

source_group(""                      FILES ${file_root})
source_group("Types"                 FILES ${file_root_types})

set(file_root
    ${file_root}
    ${file_root_types}
)

set(file_root_lua
)

set(file_root_lua_types
)

set(file_root_lua_types_vector
    lua/types/vector/vector_index_tests.lua
    lua/types/vector/vector_operator_tests.lua
)

set(file_root_lua
    ${file_root_lua}
    ${file_root_lua_types}
    ${file_root_lua_types_vector}
)
