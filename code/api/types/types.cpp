
#include "api/types/types.h"

#include "vector.h"

namespace api
{
    namespace types
    {
        void registerTypes(lua_State* L)
        {
            return luabind::module(L)[
                vector::registerScope()
            ];
        }
    }
}