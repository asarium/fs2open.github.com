#pragma once

extern "C" {
#include <lua.h>
}
#include <luabind/luabind.hpp>

namespace api
{
    namespace types
    {
        void registerTypes(lua_State*);
    }
}