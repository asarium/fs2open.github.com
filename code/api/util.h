
#pragma once

#ifdef DOXYGEN_PARSER
#define SCRIPT_PROPERTY(content) content ;
#else
#define SCRIPT_PROPERTY(content)
#endif

namespace api
{
    class library
    {
    protected:
        library() = delete;
        library(const library&) = delete;

    public:
        virtual ~library() {}
    };
}
