#pragma once

#include "globalincs/pstypes.h"

#include "api/util.h"

#include <luabind/luabind.hpp>

namespace api
{
    namespace types
    {
		/**
		 * Game event
		 */
        class gameevent
        {
        private:
            int m_index;

        public:
            /**
             * @notscriptingapi
             */
            explicit gameevent(int index);

            /**
             * @brief Gets the name of the event
             * @return The name
             * @tostringoperator
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
             * @brief The name of the gameevent
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
