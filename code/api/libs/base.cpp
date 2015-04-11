
#include <functional>

#include "globalincs/pstypes.h"
#include "freespace.h"
#include "network/multi.h"
#include "playerman/player.h"

#include "api/libs/base.h"
#include "api/types/gameevent.h"

#include <luabind/class.hpp>
#include <gamesequence/gamesequence.h>

namespace
{
    using namespace api;
    using namespace api::types;
    using namespace api::libs;

    vector createVector0()
    {
        return base::createVector(0.0f, 0.0f, 0.0f);
    }

    vector createVector1(float a)
    {
        return base::createVector(a, 0.0f, 0.0f);
    }

    vector createVector2(float a, float b)
    {
        return base::createVector(a, b, 0.0f);
    }

    api::types::matrix createOrientation0()
    {
        return api::types::matrix();
    }

    api::types::matrix createOrientation3(float p, float b, float h)
    {
        return api::types::matrix(p, b, h);
    }

    float getFrametimeFalse()
    {
        return base::getFrametime(false);
    }

    void setTipsFalse()
    {
        base::setTips(false);
    }
}

namespace api
{
    namespace libs
    {
        void base::print(const char* msg)
        {
            mprintf(("%s", msg));
        }

        void base::warning(const char* msg)
        {
            Warning(LOCATION, "%s", msg);
        }

        void base::error(const char* msg)
        {
            Error(LOCATION, "%s", msg);
        }

        types::vector base::createVector(float a, float b, float c)
        {
            return types::vector(a, b, c);
        }

        types::matrix base::createOrientation(float r1c1, float r1c2, float r1c3,
            float r2c1, float r2c2, float r2c3,
            float r3c1, float r3c2, float r3c3)
        {
            return types::matrix(r1c1, r1c2, r1c3,
                r2c1, r2c2, r2c3,
                r3c1, r3c2, r3c3);
        }

        float base::getFrametime(bool adjustForTimeCompression)
        {
            return adjustForTimeCompression ? flRealframetime : flFrametime;
        }

        const char* base::getCurrentMPStatus()
        {
            if (MULTIPLAYER_MASTER)
                return "MULTIPLAYER_MASTER";

            if (MULTIPLAYER_HOST)
                return "MULTIPLAYER_HOST";

            if (MULTIPLAYER_CLIENT)
                return "MULTIPLAYER_CLIENT";

            if (MULTIPLAYER_STANDALONE)
                return "MULTIPLAYER_STANDALONE";

            return "SINGLEPLAYER";
        }

        const char* base::setControlMode(const luaenum& e)
        {
            switch (e.getValue())
            {
            case luaenum::LE_NORMAL_CONTROLS:
                lua_game_control |= LGC_NORMAL;
                lua_game_control &= ~(LGC_STEERING | LGC_FULL);
                return "NORMAL CONTROLS";
            case luaenum::LE_LUA_STEERING_CONTROLS:
                lua_game_control |= LGC_STEERING;
                lua_game_control &= ~(LGC_NORMAL | LGC_FULL);
                return "LUA STEERING CONTROLS";
            case luaenum::LE_LUA_FULL_CONTROLS:
                lua_game_control |= LGC_FULL;
                lua_game_control &= ~(LGC_STEERING | LGC_NORMAL);
                return "LUA FULL CONTROLS";
            default:
                return "";
            }
        }

        const char* base::setControlMode()
        {
            if (lua_game_control & LGC_NORMAL)
            {
                return "NORMAL";
            }
            else if (lua_game_control & LGC_STEERING)
            {
                return "STEERING";
            }
            else if (lua_game_control & LGC_FULL)
            {
                return "FULL";
            }
            else
            {
                return "";
            }
        }

        const char* base::setButtonControlMode()
        {
            if (lua_game_control & LGC_B_NORMAL)
                return "NORMAL";
            else if (lua_game_control & LGC_B_OVERRIDE)
                return "OVERRIDE";
            else if (lua_game_control & LGC_B_ADDITIVE)
                return "ADDITIVE";
            else
                return "";
        }

        const char* base::setButtonControlMode(const luaenum& e)
        {
            switch (e.getValue()) {
            case luaenum::LE_NORMAL_BUTTON_CONTROLS:
                lua_game_control |= LGC_B_NORMAL;
                lua_game_control &= ~(LGC_B_ADDITIVE | LGC_B_OVERRIDE);
                return "NORMAL BUTTON CONTROL";
            case luaenum::LE_LUA_ADDITIVE_BUTTON_CONTROL:
                lua_game_control |= LGC_B_ADDITIVE;
                lua_game_control &= ~(LGC_B_NORMAL | LGC_B_OVERRIDE);
                return "LUA OVERRIDE BUTTON CONTROL";
            case luaenum::LE_LUA_OVERRIDE_BUTTON_CONTROL:
                lua_game_control |= LGC_B_OVERRIDE;
                lua_game_control &= ~(LGC_B_ADDITIVE | LGC_B_NORMAL);
                return "LUA ADDITIVE BUTTON CONTROL";
            default:
                return "";
            }
        }

        void base::setTips(bool enable)
        {
            if (Player == nullptr)
                return;

            if (enable)
                Player->tips = 1;
            else
                Player->tips = 0;
        }

        luabind::scope base::registerScope()
        {
            using namespace luabind;

            return class_<base>("ba")
                .scope[
                    def("print", &base::print),
                        def("warning", &base::warning),
                        def("error", &base::error),

                        def("createVector", &createVector0),
                        def("createVector", &createVector1),
                        def("createVector", &createVector2),
                        def("createVector", &base::createVector),

                        def("createOrientation", &createOrientation0),
                        def("createOrientation", &createOrientation3),
                        def("createOrientation", &base::createOrientation),

                        def("getFrametime", &getFrametimeFalse),
                        def("getFrametime", &base::getFrametime),

                        def("getCurrentMPStatus", &base::getCurrentMPStatus),

                        def("setControlMode", static_cast<const char*(*)()>(&base::setControlMode)),
                        def("setControlMode", static_cast<const char*(*)(const luaenum&)>(&base::setControlMode)),

                        def("setButtonControlMode", static_cast<const char*(*)()>(&base::setButtonControlMode)),
                        def("setButtonControlMode", static_cast<const char*(*)(const luaenum&)>(&base::setButtonControlMode)),

                        def("setTips", &base::setTips),
                        def("setTips", &setTipsFalse),

                        class_<GameEvents>("GameEvents")
                        .scope[
                            def("get", static_cast<gameevent(*)(const char*)>(&GameEvents::get)),
                                def("get", static_cast<gameevent(*)(int)>(&GameEvents::get)),
                            def("count", &GameEvents::count)
                        ]
                ];
        }

        gameevent base::GameEvents::get(const char* key)
        {
            return gameevent(gameseq_get_event_idx(key));
        }
        gameevent base::GameEvents::get(int index)
        {
            return gameevent(index);
        }

        size_t base::GameEvents::count()
        {
            return Num_gs_event_text;
        }
    }
}
