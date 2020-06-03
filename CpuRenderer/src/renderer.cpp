#include "renderer.h"

void CPURenderer::Renderer::render_loop()
{
	if (_frame_count % 2 < 1)
	{
		for (int i = 0; i < gViewPort.width; ++i)
		{
			for (int j = 0; j < gViewPort.height; ++j)
			{
				gViewPort.SetPixel(i, j, 255, 255, 0);
			}
		}
	}
	else
	{
		for (int i = 0; i < gViewPort.width; ++i)
		{
			for (int j = 0; j < gViewPort.height; ++j)
			{
				gViewPort.SetPixel(i, j, 0, 255, 255);
			}
		}
	}

	++_frame_count;
}
