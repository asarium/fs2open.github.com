
#include "globalincs/pstypes.h"

#include "api/types/enum.h"

#include <luabind/object.hpp>
#include <luabind/operator.hpp>
#include <luabind/class.hpp>

namespace
{
    // MAKE SURE TO CHANGE THESE IF YOU ADD A NEW VALUE!
    const char* enumNames[] = {
        "MOUSE_RIGHT_BUTTON",
        "MOUSE_MIDDLE_BUTTON",
        "PARTICLE_DEBUG",
        "PARTICLE_BITMAP",
        "PARTICLE_FIRE",
        "PARTICLE_SMOKE",
        "PARTICLE_SMOKE2",
        "PARTICLE_PERSISTENT_BITMAP",
        "TEXTURE_STATIC",
        "TEXTURE_DYNAMIC",
        "LOCK",
        "UNLOCK",
        "NONE",
        "SHIELD_FRONT",
        "SHIELD_LEFT",
        "SHIELD_RIGHT",
        "SHIELD_BACK",
        "ALPHABLEND_FILTER",
        "ALPHABLEND_NONE",
        "CFILE_TYPE_NORMAL",
        "CFILE_TYPE_MEMORY_MAPPED",
        "ORDER_ATTACK",
        "ORDER_ATTACK_ANY",
        "ORDER_DEPART",
        "ORDER_DISABLE",
        "ORDER_DISARM",
        "ORDER_DOCK",
        "ORDER_EVADE",
        "ORDER_FLY_TO",
        "ORDER_FORM_ON_WING",
        "ORDER_GUARD",
        "ORDER_IGNORE",
        "ORDER_KEEP_SAFE_DISTANCE",
        "ORDER_PLAY_DEAD",
        "ORDER_REARM",
        "ORDER_STAY_NEAR",
        "ORDER_STAY_STILL",
        "ORDER_UNDOCK",
        "ORDER_WAYPOINTS",
        "ORDER_WAYPOINTS_ONCE",
        "ORDER_ATTACK_WING",
        "ORDER_GUARD_WING",
        "SEXPVAR_CAMPAIGN_PERSISTENT",
        "SEXPVAR_NOT_PERSISTENT",
        "SEXPVAR_PLAYER_PERSISTENT",
        "SEXPVAR_TYPE_NUMBER",
        "SEXPVAR_TYPE_STRING",
        "MISSION_REPEAT",
        "NORMAL_CONTROLS",
        "LUA_STEERING_CONTROLS",
        "LUA_FULL_CONTROLS",
        "NORMAL_BUTTON_CONTROLS",
        "LUA_ADDITIVE_BUTTON_CONTROL",
        "LUA_OVERRIDE_BUTTON_CONTROL",
        "VM_INTERNAL",
        "VM_EXTERNAL",
        "VM_TRACK",
        "VM_DEAD_VIEW",
        "VM_CHASE",
        "VM_OTHER_SHIP",
        "VM_EXTERNAL_CAMERA_LOCKED",
        "VM_WARP_CHASE",
        "VM_PADLOCK_UP",
        "VM_PADLOCK_REAR",
        "VM_PADLOCK_LEFT",
        "VM_PADLOCK_RIGHT",
        "VM_WARPIN_ANCHOR",
        "VM_TOPDOWN",
        "VM_FREECAMERA"
    };

    const size_t numEnumNames = sizeof(enumNames) / sizeof(enumNames[0]);

    std::ostream& operator<<(std::ostream& out, const api::types::luaenum& v)
    {
        out << v.tostring();
        return out;
    }
}

namespace api
{
    namespace types
    {
        luaenum::luaenum(Values val) : val(val) {}

        const char* luaenum::tostring() const
        {
            auto integerVal = static_cast<size_t>(val);
            Assertion(integerVal >= 0 && integerVal < numEnumNames, "Enum value is out of range!");

            return enumNames[integerVal];
        }

        bool luaenum::operator==(const luaenum& other) const
        {
            return val == other.val;
        }

        luaenum::Values luaenum::getValue() const
        {
            return val;
        }

        luabind::scope luaenum::registerScope()
        {
            using namespace luabind;

            return class_<luaenum>("luaenum")
                .def(const_self == other<luaenum>())
                .def(luabind::tostring(const_self));
        }

        void luaenum::initializeEnumValues(lua_State* L)
        {
            using namespace luabind;

            auto max = static_cast<size_t>(Values::NUM_VALUES);
            for (size_t i = 0; i < max; ++i)
            {
                object enumObj(L, luaenum(static_cast<Values>(i)));
                globals(L)[enumNames[i]] = enumObj;
            }
        }
    }
}
