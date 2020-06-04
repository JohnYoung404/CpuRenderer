#pragma once
#include "viewport.h"
#include "point2d.h"

namespace CPURenderer
{
	class Renderer
	{
	private:
		unsigned int _frame_count;
	public:
		Renderer() :_frame_count(0) {}
		~Renderer() {}
		void draw_DDA_line(Point2d p0, Point2d p1, Color c) const;
		void render_clear() const;	// clear buffer to black.
		void render_loop();
	};
}
