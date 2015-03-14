
#include "globalincs/pstypes.h"

#include "api/libs/base.h"

#include <luabind/luabind.hpp>
#include <luabind/adopt_policy.hpp>

#include <boost/optional.hpp>

namespace
{
    api::types::vector createVector0()
    {
        return api::libs::base::createVector(0.0f, 0.0f, 0.0f);
    }

    api::types::vector createVector1(float a)
    {
        return api::libs::base::createVector(a, 0.0f, 0.0f);
    }

    api::types::vector createVector2(float a, float b)
    {
        return api::libs::base::createVector(a, b, 0.0f);
    }

    void testoptional(boost::optional<float> x)
    {
        mprintf((""));
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

                    def("testoptional", &testoptional)
                ];
        }
    }
}
