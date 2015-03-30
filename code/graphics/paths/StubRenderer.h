
#pragma once

#include "graphics/paths/PathRenderer.h"

namespace graphics
{
    namespace paths
    {
        class StubRenderer : public PathRenderer
        {
        public:
            StubRenderer() {}
            virtual ~StubRenderer() {}

            virtual void beginFrame() override {};

            virtual void cancelFrame() override {};

            virtual void endFrame() override {};

            virtual void scissor(float x, float y, float w, float h) override {};

            virtual void resetScissor() override {};

            virtual void resetTransform() override {};

            virtual void translate(float x, float y) override {};

            virtual void rotate(float rad) override {};

            virtual void skewX(float rad) override {};

            virtual void skewY(float rad) override {};

            virtual void scale(float x, float y) override {};

            virtual DrawPaint createLinearGradient(float sx, float sy, float ex,
                float ey, color* icol, color* ocol) override { return DrawPaint(); };

            virtual void setAlpha(float alpha) override {};

            virtual void setFillColor(color* color) override {};

            virtual void setFillPaint(const DrawPaint& paint) override {};

            virtual void setStrokeColor(color* color) override {};

            virtual void setStrokePaint(const DrawPaint& paint) override {};

            virtual void setStrokeWidth(float witdh) override {};

            virtual void beginPath() override {};

            virtual void moveTo(float x, float y) override {};

            virtual void setSolidity(Solidity solid) override {};

            virtual void lineTo(float x, float y) override {};

            virtual void rectangle(float x, float y, float w, float h) override {};

            virtual void roundedRectangle(float x, float y, float w, float h, float radius) override {};

            virtual void circle(float x, float y, float r) override {};

            virtual void ellipse(float x, float y, float rx, float ry) override {};

            virtual void arc(float cx, float cy, float r, float a0, float a1, Direction dir) override {};

            virtual void closePath() override {};

            virtual void fill() override {};

            virtual void stroke() override {};

            virtual void saveState() override {};

            virtual void resetState() override {};

            virtual void restoreState() override {};
        };
    }
}
