#pragma once

#include <memory>

#include "globalincs/pstypes.h"

struct NVGcontext;
namespace graphics
{
	namespace paths
	{
		class PathRenderer
		{
		private:
			static std::unique_ptr<PathRenderer> s_instance;

			NVGcontext* m_context;

			PathRenderer();
		public:
			~PathRenderer();

			static bool init();

			static inline PathRenderer* instance()
			{
				return s_instance.get();
			}

			static void shutdown();

			void beginFrame();

			void cancelFrame();

			void endFrame();

			void setAlpha(float alpha);

			void setFillColor(float r, float g, float b, float a);

			void setStrokeColor(float r, float g, float b, float a);

			void beginPath();

			void moveTo(float x, float y);

			void lineTo(float x, float y);

			void rectangle(float x, float y, float w, float h);

			void roundedRectangle(float x, float y, float w, float h, float radius);

			void circle(float x, float y, float r);

			void ellipse(float x, float y, float rx, float ry);

			void fill();

			void stroke();
		};
	}
}

