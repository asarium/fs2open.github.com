
#include "api/types/gameevent.h"

#include "gamesequence/gamesequence.h"

#include <luabind/operator.hpp>

namespace
{
    std::ostream& operator<<(std::ostream& s, const api::types::gameevent& e)
    {
        s << e.tostring();
        return s;
    }
}

namespace api
{
    namespace types
    {
        gameevent::gameevent(int index) : m_index(index)
        {
        }

        const char* gameevent::tostring() const
        {
            if (m_index < 0 || m_index >= Num_gs_event_text)
            {
                return "";
            }

            return GS_event_text[m_index];
        }

        luabind::scope gameevent::registerScope()
        {
            using namespace luabind;

            return class_<gameevent>("gameevent")
                .property("Name", &gameevent::tostring)
                .def(luabind::tostring(const_self));
        }
    }
}
