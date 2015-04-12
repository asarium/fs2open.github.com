#pragma once

#include "globalincs/pstypes.h"

#include "api/util.h"

#include <luabind/luabind.hpp>

namespace api
{
    namespace types
    {
        class gamestate
        {
        private:
            int m_index;

        public:
            explicit gamestate(int index);

            const char* tostring() const;

            bool isValid() const;

            inline int getIndex() const { return m_index; }

            SCRIPT_PROPERTY(const char* Name);

            static luabind::scope registerScope();
        };
    }
}