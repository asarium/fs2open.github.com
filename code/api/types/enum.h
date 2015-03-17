#pragma once

#include "globalincs/pstypes.h"

#include "api/types/types.h"

namespace api
{
    namespace types
    {
        class luaenum
        {
        public:
            // MAKE SURE TO ADD THE STRING VALUE IF YOU ADD A NEW VALUE!
            enum class Values
            {
                MOUSE_RIGHT_BUTTON = 0,
                MOUSE_MIDDLE_BUTTON,
                PARTICLE_DEBUG,
                PARTICLE_BITMAP,
                PARTICLE_FIRE,
                PARTICLE_SMOKE,
                PARTICLE_SMOKE2,
                PARTICLE_PERSISTENT_BITMAP,
                TEXTURE_STATIC,
                TEXTURE_DYNAMIC,
                LOCK,
                UNLOCK,
                NONE,
                SHIELD_FRONT,
                SHIELD_LEFT,
                SHIELD_RIGHT,
                SHIELD_BACK,
                ALPHABLEND_FILTER,
                ALPHABLEND_NONE,
                CFILE_TYPE_NORMAL,
                CFILE_TYPE_MEMORY_MAPPED,
                ORDER_ATTACK,
                ORDER_ATTACK_ANY,
                ORDER_DEPART,
                ORDER_DISABLE,
                ORDER_DISARM,
                ORDER_DOCK,
                ORDER_EVADE,
                ORDER_FLY_TO,
                ORDER_FORM_ON_WING,
                ORDER_GUARD,
                ORDER_IGNORE,
                ORDER_KEEP_SAFE_DISTANCE,
                ORDER_PLAY_DEAD,
                ORDER_REARM,
                ORDER_STAY_NEAR,
                ORDER_STAY_STILL,
                ORDER_UNDOCK,
                ORDER_WAYPOINTS,
                ORDER_WAYPOINTS_ONCE,
                ORDER_ATTACK_WING,
                ORDER_GUARD_WING,
                SEXPVAR_CAMPAIGN_PERSISTENT,
                SEXPVAR_NOT_PERSISTENT,
                SEXPVAR_PLAYER_PERSISTENT,
                SEXPVAR_TYPE_NUMBER,
                SEXPVAR_TYPE_STRING,
                MISSION_REPEAT,
                NORMAL_CONTROLS,
                LUA_STEERING_CONTROLS,
                LUA_FULL_CONTROLS,
                NORMAL_BUTTON_CONTROLS,
                LUA_ADDITIVE_BUTTON_CONTROL,
                LUA_OVERRIDE_BUTTON_CONTROL,
                VM_INTERNAL,
                VM_EXTERNAL,
                VM_TRACK,
                VM_DEAD_VIEW,
                VM_CHASE,
                VM_OTHER_SHIP,
                VM_EXTERNAL_CAMERA_LOCKED,
                VM_WARP_CHASE,
                VM_PADLOCK_UP,
                VM_PADLOCK_REAR,
                VM_PADLOCK_LEFT,
                VM_PADLOCK_RIGHT,
                VM_WARPIN_ANCHOR,
                VM_TOPDOWN,
                VM_FREECAMERA,
                NUM_VALUES
            };

            luaenum(Values val);

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