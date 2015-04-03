
#pragma once

#include <memory>

#include "globalincs/pstypes.h"
#include "graphics/paths/PathRenderer.h"

struct NSVGimage;
namespace svg
{
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
