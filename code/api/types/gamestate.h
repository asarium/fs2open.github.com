#pragma once

#include "globalincs/pstypes.h"

#include "api/util.h"

#include <luabind/luabind.hpp>

namespace api
{
    namespace types
    {
		/**
		 * A game state
         *
         * @ingroup GRP_SCRIPTING_API_TYPES
		 */
        class gamestate
        {
        private:
            int m_index;

        public:
            /**
             * Constructor
             * @notscriptingapi
             * @param index The state index
             */
            explicit gamestate(int index);

            /**
             * Game state name
             * @tostringoperator
             * @return Game state name, or empty string if handle is invalid
             */
            const char* tostring() const;

            /**
             * @notscriptingapi
             */
            bool isValid() const;

            /**
             * @notscriptingapi
             */
            inline int getIndex() const { return m_index; }

            /**
             * Game state name, or empty string if handle is invalid
             * @readonly{tostring}
             */
            SCRIPT_PROPERTY(const char* Name);

            /**
             * @notscriptingapi
             */
            static luabind::scope registerScope();
        };
    }
}
