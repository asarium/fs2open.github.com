#pragma once

#include "globalincs/pstypes.h"

#include "api/types/types.h"

namespace luabind{
    struct scope;
}

namespace api
{
    namespace types
    {
        class luaenum
        {
        public:
            // MAKE SURE TO ADD THE STRING VALUE IF YOU ADD A NEW VALUE!
            enum Values
            {
                LE_MOUSE_RIGHT_BUTTON = 0,
                LE_MOUSE_MIDDLE_BUTTON,
                LE_PARTICLE_DEBUG,
                LE_PARTICLE_BITMAP,
                LE_PARTICLE_FIRE,
                LE_PARTICLE_SMOKE,
                LE_PARTICLE_SMOKE2,
                LE_PARTICLE_PERSISTENT_BITMAP,
                LE_TEXTURE_STATIC,
                LE_TEXTURE_DYNAMIC,
                LE_LOCK,
                LE_UNLOCK,
                LE_NONE,
                LE_SHIELD_FRONT,
                LE_SHIELD_LEFT,
                LE_SHIELD_RIGHT,
                LE_SHIELD_BACK,
                LE_ALPHABLEND_FILTER,
                LE_ALPHABLEND_NONE,
                LE_CFILE_TYPE_NORMAL,
                LE_CFILE_TYPE_MEMORY_MAPPED,
                LE_ORDER_ATTACK,
                LE_ORDER_ATTACK_ANY,
                LE_ORDER_DEPART,
                LE_ORDER_DISABLE,
                LE_ORDER_DISARM,
                LE_ORDER_DOCK,
                LE_ORDER_EVADE,
                LE_ORDER_FLY_TO,
                LE_ORDER_FORM_ON_WING,
                LE_ORDER_GUARD,
                LE_ORDER_IGNORE,
                LE_ORDER_KEEP_SAFE_DISTANCE,
                LE_ORDER_PLAY_DEAD,
                LE_ORDER_REARM,
                LE_ORDER_STAY_NEAR,
                LE_ORDER_STAY_STILL,
                LE_ORDER_UNDOCK,
                LE_ORDER_WAYPOINTS,
                LE_ORDER_WAYPOINTS_ONCE,
                LE_ORDER_ATTACK_WING,
                LE_ORDER_GUARD_WING,
                LE_SEXPVAR_CAMPAIGN_PERSISTENT,
                LE_SEXPVAR_NOT_PERSISTENT,
                LE_SEXPVAR_PLAYER_PERSISTENT,
                LE_SEXPVAR_TYPE_NUMBER,
                LE_SEXPVAR_TYPE_STRING,
                LE_MISSION_REPEAT,
                LE_NORMAL_CONTROLS,
                LE_LUA_STEERING_CONTROLS,
                LE_LUA_FULL_CONTROLS,
                LE_NORMAL_BUTTON_CONTROLS,
                LE_LUA_ADDITIVE_BUTTON_CONTROL,
                LE_LUA_OVERRIDE_BUTTON_CONTROL,
                LE_VM_INTERNAL,
                LE_VM_EXTERNAL,
                LE_VM_TRACK,
                LE_VM_DEAD_VIEW,
                LE_VM_CHASE,
                LE_VM_OTHER_SHIP,
                LE_VM_EXTERNAL_CAMERA_LOCKED,
                LE_VM_WARP_CHASE,
                LE_VM_PADLOCK_UP,
                LE_VM_PADLOCK_REAR,
                LE_VM_PADLOCK_LEFT,
                LE_VM_PADLOCK_RIGHT,
                LE_VM_WARPIN_ANCHOR,
                LE_VM_TOPDOWN,
                LE_VM_FREECAMERA,
                LE_NUM_VALUES
            };

            explicit luaenum(Values val);

            const char* tostring() const;

            bool operator==(const luaenum& other) const;

            Values getValue() const;

            static luabind::scope registerScope();

            static void initializeEnumValues(lua_State* L);
        private:
            Values val;
        };
    }
}