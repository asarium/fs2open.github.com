
#include "apiTest.hpp"

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

void LuaFileTest::executeScript(const char* script)
{
    luaL_loadstring(L, script);

    int err = lua_pcall(L, 0, 0, 0);

    if (err)
    {
        const char* error = lua_tostring(L, -1);
        FAIL() << error << "\n";
    }
}
