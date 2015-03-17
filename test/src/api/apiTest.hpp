
#pragma once

#include <gtest/gtest.h>

#include "parse/scripting.h"

namespace api
{
    class LuaStateTest : public testing::Test
    {
    public:
        lua_State* L;

        virtual void SetUp() override
        {
            Script_system.CreateLuaState();
            L = Script_system.GetLuaSession();
        }

        virtual void TearDown() override
        {
            lua_close(L);
        }
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
}
