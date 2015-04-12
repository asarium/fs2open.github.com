
#pragma once

#include "globalincs/pstypes.h"

#include "api/util.h"

#include <luabind/luabind.hpp>

namespace api
{
    namespace types
    {
        class player
        {
        private:
            int m_index;

        public:
            explicit player(int index);

            bool isValid() const;

            const char* getName() const;

            const char* getCampaignFilename() const;

            const char* getImageFilename() const;

            std::string getMainHallName() const;

            int getMainHallIndex() const;

            const char* getSquadronName() const;

            const char* getMultiSquadronName() const;


            inline int getIndex() const { return m_index; }

            static luabind::scope registerScope();
        };
    }
}