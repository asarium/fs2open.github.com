
#pragma once

extern "C" {
#include <lua.h>
}
#include <luabind/luabind.hpp>

namespace api
{
    namespace libs
    {
        void registerLibraries(lua_State*);

        class library
        {
        private:
            library() = delete;
            library(const library&) = delete;

        public:
            virtual ~library() {}
        };
    }
}
