#pragma once
#include "viewport.h"

extern CPURenderer::ViewPort gViewPort;

namespace CPURenderer
{
	class Renderer
	{
	private:
		unsigned int _frame_count;
	public:
		Renderer() :_frame_count(0) {}
		~Renderer() {}
		void render_loop();
	};
}
