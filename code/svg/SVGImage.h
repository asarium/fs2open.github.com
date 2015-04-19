
#pragma once

#include <memory>
#include <exception>

#include "globalincs/pstypes.h"
#include "graphics/paths/PathRenderer.h"

struct NSVGimage;
namespace svg
{
    class SVGLoadException : public std::runtime_error
    {
    public:
        explicit SVGLoadException(const std::string& err) : std::runtime_error(err) {}
    };

    class SVGImage
    {
    private:
        SVGImage();

        SVGImage(const SVGImage&) = delete;
        SVGImage& operator=(const SVGImage&) = delete;

        NSVGimage* m_image;
    public:
        ~SVGImage();

        void drawImage(graphics::paths::PathRenderer* path) const;

        static std::unique_ptr<SVGImage> loadSVGFile(const SCP_string& path);
    };
}
