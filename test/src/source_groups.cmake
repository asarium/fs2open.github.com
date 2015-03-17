
set(file_root
    teststubs.cpp
)

set(file_root_api
    api/apiTest.hpp
)

set(file_root_api_types
    api/types/vector.cpp
)

set(file_root_api_lua
    api/lua/vector_tests.lua
)

source_group(""            FILES ${file_root})
source_group("API"         FILES ${file_root_api})
source_group("API\\Types"  FILES ${file_root_api_types})
source_group("API\\Lua"    FILES ${file_root_api_lua})

set(file_root
    ${file_root}
    ${file_root_api}
    ${file_root_api_lua}
    ${file_root_api_types}
)
