
#include "apiTest.hpp"

#include "freespace.h"

#include "api/lua/libs/base/base_getFrametime.lua.h"
#include "api/lua/libs/base/base_GameEvents.lua.h"

class BaseTests : public LuaFileTest
{
};

TEST_F(BaseTests, TestGetFrametime)
{
    flRealframetime = 1.0f;
    flFrametime = 2.0f;

    executeScript(api_base_getFrametime_lua);
}

TEST_F(BaseTests, GameEventsApi1)
{
    executeScript(api_base_GameEvents_lua, ScriptingApi::Version1);
}