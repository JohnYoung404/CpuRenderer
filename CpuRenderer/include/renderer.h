#pragma once
#include <Queue>
#include "viewport.h"
#include "point2d.h"
#include "vertex.h"

namespace CPURenderer
{
	class Renderer
	{
	private:
		unsigned int _frame_count;
	public:
		Renderer() :_frame_count(0) {}
		~Renderer() {}

		// input vertexes must be from convex polygon 
		std::queue<Vertex> sutherland_hodgman_clipping(std::vector<Vertex> inputVerts, Point2d x_range, Point2d y_range, Point2d z_range) const;

		void draw_DDA_line(Point2d p0, Point2d p1, Color c) const;
		void render_clear() const;	// clear buffer to black.

		void render_loop();
	};
}
