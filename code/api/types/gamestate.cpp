
#include "api/types/gamestate.h"

#include "gamesequence/gamesequence.h"

#include <luabind/operator.hpp>

namespace
{
    std::ostream& operator<<(std::ostream& s, const api::types::gamestate& e)
    {
        s << e.tostring();
        return s;
    }
}

namespace api
{
    namespace types
    {
        gamestate::gamestate(int index) : m_index(index)
        {
        }

        const char* gamestate::tostring() const
        {
            if (m_index < 0 || m_index >= Num_gs_state_text)
            {
                return "";
            }

            return GS_state_text[m_index];
        }

        bool gamestate::isValid() const
        {
            return m_index >= 0 && m_index < Num_gs_state_text;
        }

        luabind::scope gamestate::registerScope()
        {
            using namespace luabind;

            return class_<gamestate>("gamestate")
                .property("Name", &gamestate::tostring)
                .def(luabind::tostring(const_self));
        }
    }
}
