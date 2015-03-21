#pragma once

extern "C" {
#include <lua.h>
}

namespace api
{
    namespace types
    {
        void registerTypes(lua_State*);
    }
}