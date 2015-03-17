
#include "api/apiTest.hpp"

namespace api
{
    void LuaStateTest::SetUp()
    {
        state = new script_state("Test state");

        state->CreateLuaState();
        L = state->GetLuaSession();
    }

    void LuaStateTest::TearDown()
    {
        delete state;
        state = nullptr;
    }

    void LuaFileTest::SetUp()
    {
        LuaStateTest::SetUp();
    }

    void LuaFileTest::executeScript()
    {
        luaL_loadstring(L, content);

        int err = lua_pcall(L, 0, 0, 0);

        if (err)
        {
            const char* error = lua_tostring(L, -1);
            FAIL() << error << "\n";
        }
    }

    void LuaFileTest::TearDown()
    {
        LuaStateTest::TearDown();
    }
}
