
#include "apiTest.hpp"

#include "api/lua/types/vector/vector_index_tests.lua.h"
#include "api/lua/types/vector/vector_operator_tests.lua.h"
#include "api/lua/types/vector/vector_getScreenCoords.lua.h"

class VectorTests : public LuaFileTest
{
};

TEST_F(VectorTests, IndexTests)
{
    executeScript(api_vector_index_tests_lua);
}

TEST_F(VectorTests, OperatorTests)
{
    executeScript(api_vector_operator_tests_lua);
}