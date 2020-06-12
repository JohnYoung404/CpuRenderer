#pragma once
#include <vector>
#include "viewport.h"
#include "point2d.h"
#include "vertex.h"
#include "camera.h"
#include "mesh.h"
#include "texture.h"

namespace CPURenderer
{
	class Renderer
	{
	private:
		unsigned int _frame_count;
	public:
		Camera mainCamera;

		Renderer() :_frame_count(0) {}
		~Renderer() {}

		// input vertexes must be from convex polygon 
		std::vector<Vertex> sutherland_hodgman_clipping(std::vector<Vertex> inputVerts, Point2d x_range, Point2d y_range, Point2d z_range) const;

		void draw_DDA_line(const Point2d &p0, const Point2d &p1, Color c) const;
		void draw_wireframe_triangle(const Vertex &v0, const Vertex &v1, const Vertex & v2, Color c) const;
		void draw_wireframe_mesh(const Mesh &mesh, Color c) const;
		void line_sweep_fill_triangle(const Vertex &v0, const Vertex &v1, const Vertex & v2, Color c, const Texture & tex) const;
		void render_clear() const;	// clear buffer to black.

		void render_loop();
	};
}
