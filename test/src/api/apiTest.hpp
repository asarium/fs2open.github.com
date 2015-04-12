
#pragma once

#include <gtest/gtest.h>

#include "parse/scripting.h"

class LuaStateTest : public testing::Test
{
public:
    script_state* state;
    lua_State* L;

    virtual void SetUp() override;

    virtual void TearDown() override;
};

class LuaFileTest : public LuaStateTest
{
public:
    void executeScript(const char* script, ScriptingApi apiVersion = ScriptingApi::InvalidVersion);
};

class ScopedLuaStackTest
{
private:
    int top;
    lua_State* L;

public:
    ScopedLuaStackTest(lua_State* state) : L(state), top(-1)
    {
        top = lua_gettop(L);
    }

    void checkStack()
    {
        ASSERT_EQ(top, lua_gettop(L));
    }

    ~ScopedLuaStackTest()
    {
        checkStack();
    }
};
