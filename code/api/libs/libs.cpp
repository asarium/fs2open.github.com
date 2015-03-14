
#include "api/libs/libs.h"

#include "base.h"

namespace api
{
    namespace libs
    {
        void registerLibraries(lua_State* L)
        {
            return luabind::module(L)[
                base::registerScope()
            ];
        }
    }
}
