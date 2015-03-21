
#include "api/types/types.h"

#include "vector.h"
#include "matrix.h"
#include "enum.h"

#include <luabind/luabind.hpp>

namespace api
{
    namespace types
    {
        void registerTypes(lua_State* L)
        {
            return luabind::module(L, "fso")[
                vector::registerScope(),
                matrix::registerScope(),
                luaenum::registerScope()
            ];
        }
    }
}