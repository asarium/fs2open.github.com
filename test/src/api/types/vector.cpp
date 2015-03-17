
#include "apiTest.hpp"

#include "api/lua/types/vector_index_tests.lua.h"
#include "api/lua/types/vector_operator_tests.lua.h"

namespace types
{
    class VectorTest : public LuaFileTest
    {
    };

    TEST_F(VectorTest, IndexTests)
    {
        executeScript(test_vector_index_tests_lua);
    }

    TEST_F(VectorTest, OperatorTests)
    {
        executeScript(test_vector_operator_tests_lua);
    }
}