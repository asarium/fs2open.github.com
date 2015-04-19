
#include <sstream>

#include "svg/SVGImage.h"
#include "cfile/cfile.h"

#include "svg/nanosvg/nanosvg.h"

using namespace graphics::paths;
using namespace svg;

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

    DrawPaint getLinearGradient(PathRenderer* renderer, NSVGshape* shape, NSVGgradient* gradient)
    {
        return renderer->createLinearGradient(0.0f, 0.0f, 0.0f, 0.0f, getFSColor(gradient->stops[0].color), getFSColor(gradient->stops[1].color));
    }

    void setFillState(PathRenderer* renderer, NSVGshape* shape)
    {
        if (shape->fill.type == NSVG_PAINT_COLOR)
        {
            renderer->setFillColor(getFSColor(shape->fill.color));
        }
        else if (shape->fill.type == NSVG_PAINT_LINEAR_GRADIENT)
        {
            renderer->setFillPaint(getLinearGradient(renderer, shape, shape->fill.gradient));
        }
        else
        {
            mprintf(("  SVG: Sorry, only flat colors are supported right now..."));
        }
    }

    LineJoin getLineJoin(int join)
    {
        switch (join)
        {
        case NSVG_JOIN_BEVEL:
            return LineJoin::BEVEL;
        case NSVG_JOIN_MITER:
            return LineJoin::MITER;
        case NSVG_JOIN_ROUND:
            return LineJoin::ROUND;
        default:
            return LineJoin::MITER;
        }
    }

    LineCap getLineCap(int cap)
    {
        switch (cap)
        {
        case NSVG_CAP_BUTT:
            return LineCap::BUTT;
        case NSVG_CAP_ROUND:
            return LineCap::ROUND;
        case NSVG_CAP_SQUARE:
            return LineCap::SQUARE;
        default:
            return LineCap::BUTT;
        }
    }

    void setStrokeState(PathRenderer* renderer, NSVGshape* shape)
    {
        renderer->setStrokeWidth(shape->strokeWidth);
        renderer->setLineJoin(getLineJoin(shape->strokeLineJoin));
        renderer->setLineCap(getLineCap(shape->strokeLineCap));
        if (shape->stroke.type == NSVG_PAINT_COLOR)
        {
            renderer->setStrokeColor(getFSColor(shape->stroke.color));
        }
        else
        {
            mprintf(("  SVG: Sorry, only flat colors are supported right now..."));
        }
    }

    void checkSVGImage(NSVGimage* img)
    {
        for (auto shape = img->shapes; shape != NULL; shape = shape->next)
        {
            if (shape->fill.type == NSVG_PAINT_NONE && shape->stroke.type == NSVG_PAINT_NONE)
            {
                continue;
            }

            if (shape->fill.type == NSVG_PAINT_RADIAL_GRADIENT || shape->stroke.type == NSVG_PAINT_RADIAL_GRADIENT)
            {
                std::stringstream ss;
                ss << "The shape ";
                if (strlen(shape->id) <= 0)
                {
                    ss << "(unnamed shape)";
                }
                else
                {
                    ss << shape->id;
                }
                ss << " uses a radial gradient. That is currently not supported.";

                throw SVGLoadException(ss.str());
            }
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

        renderer->translate(50.f, 50.f);
        
        for (auto shape = m_image->shapes; shape != NULL; shape = shape->next)
        {
            if (shape->fill.type == NSVG_PAINT_NONE && shape->stroke.type == NSVG_PAINT_NONE)
            {
                continue;
            }

            renderer->beginPath();
            for (auto path = shape->paths; path != NULL; path = path->next)
            {
                renderer->moveTo(path->pts[0], path->pts[1]);
                for (auto i = 1; i < path->npts - 1; i += 3)
                {
                    float* p = &path->pts[i * 2];
                    renderer->bezierTo(p[0], p[1], p[2], p[3], p[4], p[5]);
                }
                if (path->closed)
                {
                    renderer->lineTo(path->pts[0], path->pts[1]);
                }
            }

            renderer->setAlpha(shape->opacity);
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

        if (image->m_image == nullptr)
        {
            throw SVGLoadException("Failed to load SVG image!");
        }

        checkSVGImage(image->m_image);

        return image;
    }
}
