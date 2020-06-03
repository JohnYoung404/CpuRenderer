#pragma once

namespace CPURenderer
{
	struct ViewPort
	{
		int width, height;
		unsigned char* frame_buffer;

		ViewPort(int aWidth, int aHeight) : width(aWidth), height(aHeight)
		{
			frame_buffer = new unsigned char[width * height * 3];
			for (int i = 0; i < width; ++i)
			{
				for (int j = 0; j < height; ++j)
				{
					SetPixel(i, j, 255, 255, 0);
				}
			}
		}
		~ViewPort()
		{
			delete[] frame_buffer;
		}

		void SetPixel(int posX, int posY, unsigned char r, unsigned char g, unsigned char b)
		{
			frame_buffer[(posX * height + posY) * 3 + 0] = r;
			frame_buffer[(posX * height + posY) * 3 + 1] = g;
			frame_buffer[(posX * height + posY) * 3 + 2] = b;
		}
	};
}

extern CPURenderer::ViewPort gViewPort;