
#include <functional>

#include "globalincs/pstypes.h"
#include "freespace.h"
#include "network/multi.h"

#include "api/libs/base.h"

#include <luabind/luabind.hpp>
#include <luabind/adopt_policy.hpp>
#include <luabind/tag_function.hpp>

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

        luabind::scope base::registerScope()
        {
            using namespace luabind;

            return namespace_("ba")
                [
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

                    def("getCurrentMPStatus", &base::getCurrentMPStatus)
                ];
        }
    }
}
