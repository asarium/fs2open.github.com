#include "graphics/paths/PathRenderer.h"

#include "graphics/gropengl.h"
#include "graphics/gropenglstate.h"

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
        GL_state.StencilTest(GL_FALSE);

        GL_state.Texture.SetActiveUnit(0);
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
}

namespace graphics
{
    namespace paths
    {
        std::unique_ptr<PathRenderer> PathRenderer::s_instance;

        PathRenderer::PathRenderer()
        {
            m_context = nvgCreateGL2(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
        }

        PathRenderer::~PathRenderer()
        {
            if (m_context)
            {
                nvgDeleteGL2(m_context);
                m_context = nullptr;
            }
        }

        bool PathRenderer::init()
        {
            s_instance = std::unique_ptr<PathRenderer>(new PathRenderer());

            return true;
        }

        void PathRenderer::shutdown()
        {
            s_instance.reset();
        }

        void PathRenderer::beginFrame()
        {
            nvgBeginFrame(m_context, gr_screen.max_w, gr_screen.max_h, 1.0f);
        }

        void PathRenderer::cancelFrame()
        {
            nvgCancelFrame(m_context);
        }

        void PathRenderer::endFrame()
        {
            nvgEndFrame(m_context);
            resetGLState();
        }

        void PathRenderer::setAlpha(float alpha)
        {
            nvgGlobalAlpha(m_context, alpha);
        }

        void PathRenderer::setFillColor(float r, float g, float b, float a)
        {
            nvgFillColor(m_context, nvgRGBAf(r, g, b, a));
        }

        void PathRenderer::setStrokeColor(float r, float g, float b, float a)
        {
            nvgStrokeColor(m_context, nvgRGBAf(r, g, b, a));
        }

        void PathRenderer::beginPath()
        {
            nvgBeginPath(m_context);
        }

        void PathRenderer::moveTo(float x, float y)
        {
            nvgMoveTo(m_context, x, y);
        }

        void PathRenderer::lineTo(float x, float y)
        {
            nvgLineTo(m_context, x, y);
        }

        void PathRenderer::rectangle(float x, float y, float w, float h)
        {
            nvgRect(m_context, x, y, w, h);
        }

        void PathRenderer::roundedRectangle(float x, float y, float w, float h, float radius)
        {
            nvgRoundedRect(m_context, x, y, w, h, radius);
        }

        void PathRenderer::circle(float x, float y, float r)
        {
            nvgCircle(m_context, x, y, r);
        }

        void PathRenderer::ellipse(float x, float y, float rx, float ry)
        {
            nvgEllipse(m_context, x, y, rx, ry);
        }

        void PathRenderer::fill()
        {
            nvgFill(m_context);
        }

        void PathRenderer::stroke()
        {
            nvgStroke(m_context);
        }
    }
}