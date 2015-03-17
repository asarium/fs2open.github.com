
#include "api/apiTest.hpp"

#include "api/lua/vector_index_tests.lua.h"

using namespace api;

class VectorTest : public LuaFileTest
{
public:
    VectorTest() : LuaFileTest(test_vector_index_tests_lua) {}
};

TEST_F(VectorTest, IndexTests)
{
    executeScript();
}