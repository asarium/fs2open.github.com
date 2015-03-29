
#pragma once

extern "C" {
#include <lua.h>
}
#include <luabind/luabind.hpp>

#include "api/util.h"

namespace api
{
    namespace libs
    {
        void registerLibraries(lua_State*);
    }
}
