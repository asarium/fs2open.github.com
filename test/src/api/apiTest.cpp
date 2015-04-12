
#include <iostream>

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

void LuaFileTest::executeScript(const char* script, ScriptingApi apiVersion)
{
    const ::testing::TestInfo* const test_info =
        ::testing::UnitTest::GetInstance()->current_test_info();

    std::stringstream ss;
    ss << test_info->test_case_name() << ": " << test_info->name();

    if (!state->EvalString(script, nullptr, nullptr, ss.str().c_str(), apiVersion))
    {
        const char* error = lua_tostring(L, -1);
        FAIL() << error << "\n";
    }
}
