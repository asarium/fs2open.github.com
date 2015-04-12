
#include "api/types/player.h"

#include "playerman/player.h"
#include "mission/missioncampaign.h"
#include "menuui/mainhallmenu.h"

namespace api
{
    namespace types
    {
        player::player(int index) : m_index(index)
        {
        }

        bool player::isValid() const
        {
            return m_index >= 0 && m_index < MAX_PLAYERS;
        }

        const char* player::getName() const
        {
            if (!isValid())
            {
                return "";
            }

            return Players[m_index].callsign;
        }

        const char* player::getCampaignFilename() const
        {
            if (!isValid())
            {
                return "";
            }

            return Players[m_index].current_campaign;
        }

        const char* player::getImageFilename() const
        {
            if (!isValid())
            {
                return "";
            }

            return Players[m_index].image_filename;
        }

        std::string player::getMainHallName() const
        {
            SCP_string* hallname = nullptr;
            // FS2-->Lua
            if (Campaign.next_mission == -1) {
                hallname = &Campaign.missions[0].main_hall;
            }
            else {
                hallname = &Campaign.missions[Campaign.next_mission].main_hall;
            }

            return std::string(hallname->begin(), hallname->end());
        }

        int player::getMainHallIndex() const
        {
            int hallnum = 0;
            //FS2-->Lua
            if (Campaign.next_mission == -1) {
                hallnum = main_hall_get_index(Campaign.missions[0].main_hall);
            }
            else {
                hallnum = main_hall_get_index(Campaign.missions[Campaign.next_mission].main_hall);
            }

            return hallnum;
        }

        const char* player::getSquadronName() const
        {
            if (!isValid())
            {
                return "";
            }

            return Players[m_index].s_squad_name;
        }

        const char* player::getMultiSquadronName() const
        {
            if (!isValid())
            {
                return "";
            }

            return Players[m_index].m_squad_name;
        }

        
        luabind::scope player::registerScope()
        {
            using namespace luabind;

            return class_<player>("player")
                .def("isValid", &player::isValid)
                .def("getName", &player::getName)
                .def("getCampaignFilename", &player::getCampaignFilename)
                .def("getImageFilename", &player::getImageFilename)
                .def("getMainHallName", &player::getMainHallName)
                .def("getMainHallIndex", &player::getMainHallIndex)
                .def("getSquadronName", &player::getSquadronName)
                .def("getMultiSquadronName", &player::getMultiSquadronName);
        }
    }
}
