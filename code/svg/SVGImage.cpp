
#include "svg/SVGImage.h"
#include "cfile/cfile.h"

#include "svg/nanosvg/nanosvg.h"

using namespace graphics::paths;

namespace
{
    color getFSColor(int col)
    {
        color c;
        c.red = static_cast<ubyte>(col & 0xff);
        c.green = static_cast<ubyte>((col >> 8) & 0xff);
        c.blue = static_cast<ubyte>((col >> 16) & 0xff);
        c.alpha = static_cast<ubyte>((col >> 24) & 0xff);
        c.is_alphacolor = true;

        return c;
    }

    void setFillState(PathRenderer* renderer, NSVGshape* shape)
    {
        if (shape->fill.type == NSVG_PAINT_COLOR)
        {
            renderer->setFillColor(getFSColor(shape->fill.color));
        }
        else
        {
            mprintf(("  SVG: Sorry, only flat colors are supported right now..."));
        }
    }

    void setStrokeState(PathRenderer* renderer, NSVGshape* shape)
    {
        renderer->setStrokeWidth(shape->strokeWidth);
        if (shape->stroke.type == NSVG_PAINT_COLOR)
        {
            renderer->setStrokeColor(getFSColor(shape->stroke.color));
        }
        else
        {
            mprintf(("  SVG: Sorry, only flat colors are supported right now..."));
        }
    }
}

namespace svg
{
    SVGImage::SVGImage() : m_image(nullptr) {}

    SVGImage::~SVGImage()
    {
        if (m_image)
        {
            nsvgDelete(m_image);
            m_image = nullptr;
        }
    }

    void SVGImage::drawImage(PathRenderer* renderer) const
    {
        renderer->saveState();

        for (auto shape = m_image->shapes; shape != NULL; shape = shape->next)
        {
            if (shape->fill.type == NSVG_PAINT_NONE && shape->stroke.type == NSVG_PAINT_NONE)
            {
                continue;
            }

            for (auto path = shape->paths; path != NULL; path = path->next)
            {
                renderer->beginPath();

                for (auto i = 0; i < path->npts - 1; i += 3)
                {
                    float* p = &path->pts[i * 2];
                    renderer->bezierTo(p[0], p[1], p[2], p[3], p[4], p[5]);
                }

                if (path->closed)
                {
                    renderer->closePath();
                }
            }

            if (shape->fill.type != NSVG_PAINT_NONE)
            {
                setFillState(renderer, shape);
                renderer->fill();
            }
            if (shape->stroke.type != NSVG_PAINT_NONE)
            {
                setStrokeState(renderer, shape);
                renderer->stroke();
            }
        }

        renderer->restoreState();
    }

    std::unique_ptr<SVGImage> SVGImage::loadSVGFile(const SCP_string& path)
    {
        auto file = cfopen(path.c_str(), "rb", CFILE_NORMAL, CF_TYPE_INTERFACE);

        if (!file)
        {
            return nullptr;
        }


        SCP_string contents;
        contents.resize(cfilelength(file));
        cfread(&contents[0], 1, contents.size(), file);

        cfclose(file);

        auto image = std::unique_ptr<SVGImage>(new SVGImage());
        image->m_image = nsvgParse(&contents[0], "px", 96.0f);

        return image;
    }
}
