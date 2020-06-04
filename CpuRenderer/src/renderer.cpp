#include <cmath>
#include "renderer.h"


void CPURenderer::Renderer::draw_DDA_line(Point2d p0, Point2d p1, Color c) const
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

void CPURenderer::Renderer::render_clear() const
{
	int width = ViewPort::instance.width;
	int height = ViewPort::instance.height;
	memset(ViewPort::instance.frame_buffer, 0, width * height * sizeof(unsigned int));
}

void CPURenderer::Renderer::render_loop()
{	
	if (_frame_count % 480 < 240)
	{
		for (int i = 0; i < ViewPort::instance.width; ++i)
		{
			for (int j = 0; j < ViewPort::instance.height; ++j)
			{
				ViewPort::instance.SetPixel(i, j, Color{255, 255, 0});
			}
		}
	}
	else
	{
		for (int i = 0; i < ViewPort::instance.width; ++i)
		{
			for (int j = 0; j < ViewPort::instance.height; ++j)
			{
				ViewPort::instance.SetPixel(i, j, Color{ 0, 255, 255});
			}
		}
	}

	render_clear();

	draw_DDA_line({ 100, 100 }, { 500, 500 }, Color::red);
	draw_DDA_line({ 500, 100 }, { 100, 500 }, Color::blue);
	draw_DDA_line({ 500, 300 }, { 100, 300 }, Color::green);

	++_frame_count;
}
