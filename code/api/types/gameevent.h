#pragma once

#include "globalincs/pstypes.h"

#include "api/util.h"

#include <luabind/luabind.hpp>

namespace api
{
    namespace types
    {
        class gameevent
        {
        private:
            int m_index;

        public:
            explicit gameevent(int index);

            const char* tostring() const;

            SCRIPT_PROPERTY(const char* Name);

            static luabind::scope registerScope();
        };
    }
}