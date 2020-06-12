#include <cmath>
#include <vector>
#include <algorithm>
#include "renderer.h"
#include "math_util.h"
#include "matrix4.h"

void CPURenderer::Renderer::render_clear() const
{
	int width = ViewPort::instance.width;
	int height = ViewPort::instance.height;
	memset(ViewPort::instance.frame_buffer, 0, width * height * sizeof(unsigned int));
}

void drawTri(const CPURenderer::Renderer &r, CPURenderer::Vector4 p0, CPURenderer::Vector4 p1, CPURenderer::Vector4 p2)
{
	using namespace CPURenderer;
	Vector4 t0 = r.mainCamera.ScrMappingMat() * r.mainCamera.ProjMat() * r.mainCamera.ViewMat() * p0;
	Vector4 t1 = r.mainCamera.ScrMappingMat() * r.mainCamera.ProjMat() * r.mainCamera.ViewMat() * p1;
	Vector4 t2 = r.mainCamera.ScrMappingMat() * r.mainCamera.ProjMat() * r.mainCamera.ViewMat() * p2;

	Vertex sv0 = { {t0.x / t0.w, t0.y / t0.w, t0.z / t0.w}, 1.0f, 1.0f };
	Vertex sv1 = { {t1.x / t1.w, t1.y / t1.w, t1.z / t1.w}, 1.0f, 0.0f };
	Vertex sv2 = { {t2.x / t2.w, t2.y / t2.w, t2.z / t2.w}, 0.0f, 1.0f };

	r.draw_wireframe_triangle(sv0, sv1, sv2, Color::white);
}

void CPURenderer::Renderer::render_loop()
{	
	if (_frame_count % 480 < 240)
	{
		for (int i = 0; i < ViewPort::instance.width; ++i)
		{
			for (int j = 0; j < ViewPort::instance.height; ++j)
			{
				ViewPort::instance.SetPixel(i, j, Color::yellow);
			}
		}
	}
	else
	{
		for (int i = 0; i < ViewPort::instance.width; ++i)
		{
			for (int j = 0; j < ViewPort::instance.height; ++j)
			{
				ViewPort::instance.SetPixel(i, j, Color::sky_blue);
			}
		}
	}
	render_clear();
	ViewPort::instance.ZBufferClear();

	//Vertex x0{ {1000, 200, 0} }, x1{ {-400, 500, 0} }, x2{ {300, -100, 0} };
	//Vertex y0{ {20, 200, 0} }, y1{ {300, 500, 0} }, y2{ {1700, 100, 0} };
	//draw_wireframe_triangle(x0, x1, x2, Color::yellow);
	//draw_wireframe_triangle(y0, y1, y2, Color::red);

	//drawTri(*this, { 1.0f, 1.0f, -1.0f, 1.0f }, { 1.0f, -1.0f, -1.0f, 1.0f }, { -1.0f, 1.0f, -1.0f, 1.0f });
	//drawTri(*this, { -1.0f, -1.0f, -1.0f, 1.0f }, { 1.0f, -1.0f, -1.0f, 1.0f }, { -1.0f, 1.0f, -1.0f, 1.0f });
	//drawTri(*this, { 1.0f, 1.0f, -1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, -1.0f, -1.0f, 1.0f });
	//drawTri(*this, { 1.0f, -1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, -1.0f, -1.0f, 1.0f });
	//drawTri(*this, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, -1.0f, 1.0f, 1.0f }, { -1.0f, 1.0f, 1.0f, 1.0f });
	//drawTri(*this, { -1.0f, 1.0f, 1.0f, 1.0f }, { -1.0f, -1.0f, 1.0f, 1.0f }, { 1.0f, -1.0f, 1.0f, 1.0f });
	//drawTri(*this, { -1.0f, 1.0f, -1.0f, 1.0f }, { -1.0f, -1.0f, -1.0f, 1.0f }, { -1.0f, 1.0f, 1.0f, 1.0f });
	//drawTri(*this, { -1.0f, -1.0f, 1.0f, 1.0f }, { -1.0f, -1.0f, -1.0f, 1.0f }, { -1.0f, 1.0f, 1.0f, 1.0f });
	//drawTri(*this, { -1.0f, -1.0f, -1.0f, 1.0f }, { 1.0f, -1.0f, -1.0f, 1.0f }, { 1.0f, -1.0f, 1.0f, 1.0f });
	//drawTri(*this, { -1.0f, -1.0f, -1.0f, 1.0f }, { -1.0f, -1.0f, 1.0f, 1.0f }, { 1.0f, -1.0f, 1.0f, 1.0f });
	//drawTri(*this, { 1.0f, 1.0f, -1.0f, 1.0f }, { -1.0f, 1.0f, -1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f });
	//drawTri(*this, { -1.0f, 1.0f, 1.0f, 1.0f }, { -1.0f, 1.0f, -1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f });
	
	//////////////////////////////////////////////////////////////////////////
	// math test.
	//Matrix4 m =
	//{
	//	1.0f, 2.0f, 3.0f, 4.0f,
	//	5.0f, 8.0f, 7.0f, 6.0f,
	//	4.0f, 3.0f, 2.0f, 1.0f,
	//	5.0f, 6.0f, 8.0f, 7.0f
	//};
	//Matrix4 e = m.inverse() * m;
	//////////////////////////////////////////////////////////////////////////
	++_frame_count;
}

void CPURenderer::Renderer::draw_DDA_line(const Point2d &p0, const Point2d &p1, Color c) const
{
	float dx = p1.x - p0.x;
	float dy = p1.y - p0.y;

	int step = (int)round(abs(dx) > abs(dy) ? abs(dx) : abs(dy));

	float Xinc = dx / step;
	float Yinc = dy / step;

	float X = p0.x;
	float Y = p0.y;

	for (int i = 0; i < step; ++i)
	{
		ViewPort::instance.SetPixel((int)round(X), (int)round(Y), c);
		X += Xinc;
		Y += Yinc;
	}
}

void CPURenderer::Renderer::draw_wireframe_triangle(const Vertex & v0, const Vertex & v1, const Vertex & v2, Color c) const
{
	std::vector<Vertex> convex = { v0, v1, v2 };

	std::vector<Vertex> clipped = sutherland_hodgman_clipping(convex, { 0.0f, (float)ViewPort::instance.width - 1.0f }, { 0.0f, (float)ViewPort::instance.height - 1.0f }, { -1.0f, 1.0f });

	for (int i = 0; i < (int)clipped.size(); ++i)
	{
		if (i <= (int)clipped.size() - 2)
		{
			draw_DDA_line({ clipped[i].pos.x , clipped[i].pos.y }, { clipped[i + 1].pos.x , clipped[i + 1].pos.y }, c);
		}
		else
		{
			draw_DDA_line({ clipped[i].pos.x , clipped[i].pos.y }, { clipped[0].pos.x , clipped[0].pos.y }, c);
		}

		if (i != 0) draw_DDA_line({ clipped[i].pos.x , clipped[i].pos.y }, { clipped[0].pos.x , clipped[0].pos.y }, c);
	}
}

void CPURenderer::Renderer::draw_wireframe_mesh(const Mesh & mesh, Color c) const
{
	if (!mesh.mesh.size())	return;
	const auto &verts = mesh.mesh[0].mesh.positions;
	const auto &coords = mesh.mesh[0].mesh.texcoords;
	const auto &indices = mesh.mesh[0].mesh.indices;
	const Matrix4 &mvp = mainCamera.ScrMappingMat() * mainCamera.ProjMat()* mainCamera.ViewMat();
	for (size_t i = 0; i < indices.size(); i += 3)
	{
		size_t indice_0 = indices[i], indice_1 = indices[i + 1], indice_2 = indices[i + 2];
		Vector4 v0 = { verts[indice_0 * 3], verts[indice_0 * 3 + 1], verts[indice_0 * 3 + 2], 1.0f };
		Vector4 v1 = { verts[indice_1 * 3], verts[indice_1 * 3 + 1], verts[indice_1 * 3 + 2], 1.0f };
		Vector4 v2 = { verts[indice_2 * 3], verts[indice_2 * 3 + 1], verts[indice_2 * 3 + 2], 1.0f };

		Vector4 t0 = mvp * v0;
		Vector4 t1 = mvp * v1;
		Vector4 t2 = mvp * v2;

		Vertex sv0, sv1, sv2;

		sv0.pos = { t0.x / t0.w, t0.y / t0.w, t0.z / t0.w };
		sv0.xTexCoord = coords[indice_0 * 2] / t0.w;
		sv0.yTexCoord = coords[indice_0 * 2 + 1] / t0.w;
		sv0.one_div_w = 1.0f / t0.w;

		sv1.pos = { t1.x / t1.w, t1.y / t1.w, t1.z / t1.w };
		sv1.xTexCoord = coords[indice_1 * 2] / t1.w;
		sv1.yTexCoord = coords[indice_1 * 2 + 1] / t1.w;
		sv1.one_div_w = 1.0f / t1.w;

		sv2.pos = { t2.x / t2.w, t2.y / t2.w, t2.z / t2.w };
		sv2.xTexCoord = coords[indice_2 * 2] / t2.w;
		sv2.yTexCoord = coords[indice_2 * 2 + 1] / t2.w;
		sv2.one_div_w = 1.0f / t2.w;

		//back-face culling
		Vector3 norm = cross(sv1.pos - sv0.pos, sv2.pos - sv1.pos);
		if (norm.z < 0)
		{
			Vector3 modelNorm = cross(Vector3{ v1.x, v1.y, v1.z } -Vector3{ v0.x, v0.y, v0.z }, Vector3{ v2.x, v2.y, v2.z } -Vector3{ v1.x, v1.y, v1.z }).normalize();
			sv0.norm = modelNorm;
			sv1.norm = modelNorm;
			sv2.norm = modelNorm;
			//draw_wireframe_triangle(sv0, sv1, sv2, c);
			line_sweep_fill_triangle(sv0, sv1, sv2, c, mesh.tex);
		}
	}
}

namespace
{
	enum ScissorAxis
	{
		X_neg, X_pos, Y_neg, Y_pos, Z_neg, Z_pos
	};

	bool vertexInsideClippingArea(const CPURenderer::Vertex &vert, ScissorAxis axis, float boundVal)
	{
		switch (axis)
		{
		case ScissorAxis::X_neg:
			return vert.pos.x >= boundVal;
		case ScissorAxis::X_pos:
			return vert.pos.x <= boundVal;
		case ScissorAxis::Y_neg:
			return vert.pos.y >= boundVal;
		case ScissorAxis::Y_pos:
			return vert.pos.y <= boundVal;
		case ScissorAxis::Z_neg:
			return vert.pos.z >= boundVal;
		case ScissorAxis::Z_pos:
			return vert.pos.z <= boundVal;
		default:
			return false;
		}
	}

	void clip_point_pair(std::vector<CPURenderer::Vertex> &vertsQueue, CPURenderer::Vertex first, CPURenderer::Vertex second, ScissorAxis axis, float boundVal)
	{
		using namespace CPURenderer;
		using namespace CPURenderer::Math;

		bool firstPointInsideBound = vertexInsideClippingArea(first, axis, boundVal);
		bool secondPointInsideBound = vertexInsideClippingArea(second, axis, boundVal);
		LerpAxis lerpAxis = axis <= 1 ? LerpAxis::X : (axis >= 4 ? LerpAxis::Z : LerpAxis::Y);

		if (firstPointInsideBound && secondPointInsideBound)
		{
			vertsQueue.push_back(std::move(second));
		}
		else if (!firstPointInsideBound && secondPointInsideBound)
		{
			Vertex intersect = VertexLerp(first, second, boundVal, lerpAxis);
			vertsQueue.push_back(std::move(intersect));
			vertsQueue.push_back(std::move(second));
		}
		else if (firstPointInsideBound && !secondPointInsideBound)
		{
			Vertex intersect = VertexLerp(first, second, boundVal, lerpAxis);
			vertsQueue.push_back(std::move(intersect));
		}
	}

	std::vector<CPURenderer::Vertex> sutherland_hodgman_clip_by_axis(std::vector<CPURenderer::Vertex> inputVerts, ScissorAxis axis, float boundVal)
	{
		using namespace CPURenderer;
		using namespace CPURenderer::Math;

		std::vector<Vertex> ret;

		for (size_t i = 0; i < inputVerts.size(); ++i)
		{
			if (i <= inputVerts.size() - 2)
			{
				clip_point_pair(ret, inputVerts[i], inputVerts[i + 1], axis, boundVal);
			}
			else
			{
				clip_point_pair(ret, inputVerts[i], inputVerts[0], axis, boundVal);
			}
		}

		return ret;
	}

	void fill_top_flat_triangle(CPURenderer::Renderer r, const CPURenderer::Vertex & v0, const CPURenderer::Vertex & v1, const CPURenderer::Vertex & v2, CPURenderer::Color c)
	{

	}

	void fill_bottom_flat_triangle(CPURenderer::Renderer r, const CPURenderer::Vertex & v0, const CPURenderer::Vertex & v1, const CPURenderer::Vertex & v2, CPURenderer::Color c)
	{

	}

	const CPURenderer::Vector3 lightDir = { 0.0f, 0.0f, 1.0f };

	// triangle rasterization reference: 
	// http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html

	void BaryCentric_filling(const CPURenderer::Renderer& r, const CPURenderer::Vertex & v0, const CPURenderer::Vertex & v1, const CPURenderer::Vertex & v2, CPURenderer::Color c, const CPURenderer::Texture & tex)
	{
		using namespace CPURenderer;
		std::pair<float, float> xBound = std::minmax({ v0.pos.x, v1.pos.x, v2.pos.x });
		std::pair<float, float> yBound = std::minmax({ v0.pos.y, v1.pos.y, v2.pos.y });
		Vector3 vs1 = { (v1.pos - v0.pos).x, (v1.pos - v0.pos).y, 1.0f };
		Vector3 vs2 = { (v2.pos - v0.pos).x, (v2.pos - v0.pos).y, 1.0f };
		for(int x = (int)std::round(xBound.first); x <= (int)std::round(xBound.second); ++x)
			for (int y = (int)std::round(yBound.first); y <= (int)std::round(yBound.second); ++y)
			{
				Vector3 q = { x - v0.pos.x, y - v0.pos.y, 1.0f };
				float s = (q.x * vs2.y - q.y * vs2.x) / (vs1.x * vs2.y - vs1.y * vs2.x);
				float t = (vs1.x * q.y - vs1.y * q.x) / (vs1.x * vs2.y - vs1.y * vs2.x);
				if (s >= 0 && t >= 0 && s + t <= 1.0f)
				{
					// Half-Lambert
					float difLight = dot(v0.norm, lightDir);
					float fLambert = 0.5f + 0.5f * difLight;
					//Vertex lp1 = Math::VertexLerp(v0, v1, x, Math::LerpAxis::X);
					//Vertex lp2 = Math::VertexLerp(v2, lp1, y, Math::LerpAxis::Y);
					//ViewPort::instance.SetPixel((int)round(x), (int)round(y), toDraw);
					float zVal = (v1.pos.z - v0.pos.z) * s + (v2.pos.z - v0.pos.z) * t + v0.pos.z;
					float texCoordX = (v1.xTexCoord - v0.xTexCoord) * s + (v2.xTexCoord - v0.xTexCoord) * t + v0.xTexCoord;
					float texCoordY = (v1.yTexCoord - v0.yTexCoord) * s + (v2.yTexCoord - v0.yTexCoord) * t + v0.yTexCoord;
					float one_div_w = (v1.one_div_w - v0.one_div_w) * s + (v2.one_div_w - v0.one_div_w) * t + v0.one_div_w;
					Color toDraw = tex.getPixel(texCoordX / one_div_w , texCoordY / one_div_w);
					toDraw.r = (unsigned char)(fLambert * toDraw.r);
					toDraw.g = (unsigned char)(fLambert * toDraw.g);
					toDraw.b = (unsigned char)(fLambert * toDraw.b);
					ViewPort::instance.SetPixelZCheck((int)round(x), (int)round(y), toDraw, zVal);
				}
			}
	}
}

std::vector<CPURenderer::Vertex> CPURenderer::Renderer::sutherland_hodgman_clipping(std::vector<Vertex> inputVerts, Point2d x_range, Point2d y_range, Point2d z_range) const
{
	inputVerts = sutherland_hodgman_clip_by_axis(inputVerts, ScissorAxis::X_neg, x_range.x);
	inputVerts = sutherland_hodgman_clip_by_axis(inputVerts, ScissorAxis::X_pos, x_range.y);
	inputVerts = sutherland_hodgman_clip_by_axis(inputVerts, ScissorAxis::Y_neg, y_range.x);
	inputVerts = sutherland_hodgman_clip_by_axis(inputVerts, ScissorAxis::Y_pos, y_range.y);
	inputVerts = sutherland_hodgman_clip_by_axis(inputVerts, ScissorAxis::Z_neg, z_range.x);
	inputVerts = sutherland_hodgman_clip_by_axis(inputVerts, ScissorAxis::Z_pos, z_range.y);

	return inputVerts;
}

void CPURenderer::Renderer::line_sweep_fill_triangle(const Vertex & v0, const Vertex & v1, const Vertex & v2, Color c, const Texture & tex) const
{
	BaryCentric_filling(*this, v0, v1, v2, c, tex);

	//it seems without clipping below is faster:
	/*std::vector<Vertex> convex = { v0, v1, v2 };

	std::vector<Vertex> clipped = sutherland_hodgman_clipping(convex, { 0.0f, (float)ViewPort::instance.width - 1.0f }, { 0.0f, (float)ViewPort::instance.height - 1.0f }, { -1.0f, 1.0f });

	for (int i = 0; i < (int)clipped.size(); ++i)
	{
		if (i <= (int)clipped.size() - 2)
		{
			BaryCentric_filling(*this, clipped[0], clipped[i], clipped[i + 1], c);
		}
	}*/
}