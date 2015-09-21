
#pragma once

#include "globalincs/pstypes.h"

#include "api/util.h"

#include <luabind/luabind.hpp>

namespace api
{
    namespace types
    {
		/**
		 * Player handle
         *
         * @ingroup GRP_SCRIPTING_API_TYPES
		 */
        class player
        {
        private:
            int m_index;

        public:
            /**
             * @notscriptingapi
             * @param index
             */
            explicit player(int index);

            /**
             * @brief Detects whether handle is valid
             * @return true if valid, false if handle is invalid
             */
            bool isValid() const;

            /**
             * @brief Gets current player name
             * @return Player name, or empty string if handle is invalid
             */
            const char* getName() const;

            /**
             * @brief Gets current player campaign filename
             * @return Campaign name, or empty string if handle is invalid
             */
            const char* getCampaignFilename() const;

            /**
             * @brief Gets current player image filename
             * @return Player image filename, or empty string if handle is invalid
             */
            const char* getImageFilename() const;

            /**
             * @brief Gets player's current main hall name
             * @return Main hall name, or name of first mainhall in campaign if something goes wrong
             */
            std::string getMainHallName() const;

            /**
             * @brief Gets player's current main hall number
             * @return Main hall index, or index of first mainhall in campaign if something goes wrong
             */
            int getMainHallIndex() const;

            /**
             * @brief Gets current player squad name
             * @return Squadron name, or empty string if handle is invalid
             */
            const char* getSquadronName() const;

            /**
             * @brief Gets current player multi squad name
             * @return Squadron name, or empty string if handle is invalid
             */
            const char* getMultiSquadronName() const;

            /**
             * @notscriptingapi
             * @return The index of the player
             */
            inline int getIndex() const { return m_index; }

            /**
             * @notscriptingapi
             */
            static luabind::scope registerScope();
        };
    }
}
