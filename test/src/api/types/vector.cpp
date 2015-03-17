
#include "apiTest.hpp"

#include "api/lua/vector_index_tests.lua.h"

namespace types
{
    class VectorTest : public LuaFileTest
    {
    };

    TEST_F(VectorTest, IndexTests)
    {
        executeScript(test_vector_index_tests_lua);
    }
}