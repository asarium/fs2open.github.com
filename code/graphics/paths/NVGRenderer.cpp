
#include "graphics/paths/NVGRenderer.h"

#include "graphics/gropengl.h"
#include "graphics/gropenglstate.h"
#include "graphics/gropengltnl.h"

#include "nanovg/nanovg.h"
// NanoVG supports OpenGL 2 and 3, we currently use OpenGL 2
#define NANOVG_GL2_IMPLEMENTATION
#include "nanovg/nanovg_gl.h"

namespace
{
    void resetGLState()
    {
        // After we are done with nanovg we need to tell our state tracker that things have changed
        GL_state.Blend(GL_TRUE);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        GL_state.BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        GL_state.SetAlphaBlendMode(ALPHA_BLEND_ALPHA_BLEND_ALPHA);

        GL_state.CullFace(GL_FALSE);
        GL_state.CullFaceValue(GL_BACK);

        GL_state.FrontFaceValue(GL_CCW);

        GL_state.DepthTest(GL_FALSE);
        GL_state.ScissorTest(GL_FALSE);
        GL_state.ColorMask(GL_TRUE);

        GL_state.SetStencilType(STENCIL_TYPE_WRITE);
        GL_state.StencilTest(GL_TRUE);

        GL_state.Texture.SetActiveUnit(0);
        GL_state.Texture.SetTarget(0);
        GL_state.Texture.DisableAll();

        GL_state.Array.BindArrayBuffer(0);
        glUseProgram(0);

        // State that is not currently tracked by FSO:
        //   glBindBuffer(GL_UNIFORM_BUFFER, buf);
        //   glBindVertexArray(arr);
        //   glUseProgram(prog);

        // Now reset the values to what we need
        GL_state.SetStencilType(STENCIL_TYPE_NONE);
        GL_state.StencilTest(GL_FALSE);
    }

    NVGcolor fsColorToNVG(color* c)
    {
        return nvgRGBA(c->red, c->green, c->blue, c->is_alphacolor ? c->alpha : 255);
    }
}

namespace graphics
{
    namespace paths
    {
        NVGRenderer::NVGRenderer()
        {
            m_context = nvgCreateGL2(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
        }

        NVGRenderer::~NVGRenderer()
        {
            if (m_context)
            {
                nvgDeleteGL2(m_context);
                m_context = nullptr;
            }
        }

        void NVGRenderer::beginFrame()
        {
            nvgBeginFrame(m_context, gr_screen.max_w, gr_screen.max_h, 1.0f);
        }

        void NVGRenderer::cancelFrame()
        {
            nvgCancelFrame(m_context);
        }

        void NVGRenderer::endFrame()
        {
            gr_opengl_set_2d_matrix();

            nvgEndFrame(m_context);

            gr_opengl_end_2d_matrix();

            resetGLState();
        }

        void NVGRenderer::scissor(float x, float y, float w, float h)
        {
            nvgScissor(m_context, x, y, w, h);
        }

        void NVGRenderer::resetScissor()
        {
            nvgResetScissor(m_context);
        }

        void NVGRenderer::resetTransform()
        {
            nvgResetTransform(m_context);
        }

        void NVGRenderer::translate(float x, float y)
        {
            nvgTranslate(m_context, x, y);
        }

        void NVGRenderer::rotate(float rad)
        {
            nvgRotate(m_context, rad);
        }

        void NVGRenderer::skewX(float rad)
        {
            nvgSkewX(m_context, rad);
        }

        void NVGRenderer::skewY(float rad)
        {
            nvgSkewY(m_context, rad);
        }

        void NVGRenderer::scale(float x, float y)
        {
            nvgScale(m_context, x, y);
        }

        DrawPaint NVGRenderer::createLinearGradient(float sx, float sy, float ex,
            float ey, color* icol, color* ocol)
        {
            DrawPaint p;

            p.nvg = nvgLinearGradient(m_context, sx, sy, ex, ey, fsColorToNVG(icol), fsColorToNVG(ocol));

            return p;
        }

        void NVGRenderer::setAlpha(float alpha)
        {
            nvgGlobalAlpha(m_context, alpha);
        }

        void NVGRenderer::setFillColor(color* color)
        {
            nvgFillColor(m_context, fsColorToNVG(color));
        }

        void NVGRenderer::setFillPaint(const DrawPaint& paint)
        {
            nvgFillPaint(m_context, paint.nvg);
        }

        void NVGRenderer::setStrokeColor(color* color)
        {
            nvgStrokeColor(m_context, fsColorToNVG(color));
        }
        
        void NVGRenderer::setStrokePaint(const DrawPaint& paint)
        {
            nvgStrokePaint(m_context, paint.nvg);
        }

        void NVGRenderer::setStrokeWidth(float width)
        {
            nvgStrokeWidth(m_context, width);
        }

        void NVGRenderer::beginPath()
        {
            nvgBeginPath(m_context);
        }

        void NVGRenderer::moveTo(float x, float y)
        {
            nvgMoveTo(m_context, x, y);
        }

        void NVGRenderer::setSolidity(Solidity solid)
        {
            int nvgSolid;
            switch (solid)
            {
            case Solidity::HOLE:
                nvgSolid = NVG_HOLE;
                break;
            case Solidity::SOLID:
                nvgSolid = NVG_SOLID;
                break;
            default:
                nvgSolid = NVG_SOLID;
                break;
            }

            nvgPathWinding(m_context, nvgSolid);
        }

        void NVGRenderer::lineTo(float x, float y)
        {
            nvgLineTo(m_context, x, y);
        }

        void NVGRenderer::rectangle(float x, float y, float w, float h)
        {
            nvgRect(m_context, x, y, w, h);
        }

        void NVGRenderer::roundedRectangle(float x, float y, float w, float h, float radius)
        {
            nvgRoundedRect(m_context, x, y, w, h, radius);
        }

        void NVGRenderer::circle(float x, float y, float r)
        {
            nvgCircle(m_context, x, y, r);
        }

        void NVGRenderer::ellipse(float x, float y, float rx, float ry)
        {
            nvgEllipse(m_context, x, y, rx, ry);
        }

        void NVGRenderer::arc(float cx, float cy, float r, float a0, float a1, Direction dir)
        {
            int nvgDir;
            switch (dir)
            {
            case Direction::CCW:
                nvgDir = NVG_CCW;
                break;
            case Direction::CW:
                nvgDir = NVG_CW;
                break;
            default:
                nvgDir = NVG_CW;
                break;
            }

            nvgArc(m_context, cx, cy, r, a0, a1, nvgDir);
        }

        void NVGRenderer::closePath()
        {
            nvgClosePath(m_context);
        }

        void NVGRenderer::fill()
        {
            nvgFill(m_context);
        }

        void NVGRenderer::stroke()
        {
            nvgStroke(m_context);
        }

        void NVGRenderer::saveState()
        {
            nvgSave(m_context);
        }

        void NVGRenderer::resetState()
        {
            nvgReset(m_context);
        }

        void NVGRenderer::restoreState()
        {
            nvgRestore(m_context);
        }
    }
}
