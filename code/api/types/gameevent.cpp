
#include <exception>

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
            if (index < 0 || index >= Num_gs_event_text)
            {
                throw std::runtime_error("gameevent index out of range!");
            }
        }

        const char* gameevent::tostring() const
        {
            return GS_event_text[m_index];
        }

        luabind::scope gameevent::registerScope()
        {
            using namespace luabind;

            return class_<gameevent>("gameevent")
                .property("Name", &gameevent::tostring);
        }
    }
}
