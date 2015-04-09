
#pragma once

extern "C" {
#include <lua.h>
}

namespace api
{
    namespace libs
    {
        void registerLibraries(lua_State*);
    }
}
