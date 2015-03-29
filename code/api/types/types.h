#pragma once

extern "C" {
#include <lua.h>
}

#include "api/util.h"

namespace api
{
    namespace types
    {
        void registerTypes(lua_State*);
    }
}