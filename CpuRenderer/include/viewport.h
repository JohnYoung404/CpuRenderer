#pragma once
#include <SDL.h>
#include <string>

namespace CPURenderer
{
	struct ViewPort
	{
		int width, height;
		unsigned char* frame_buffer;

		ViewPort(int aWidth, int aHeight) : width(aWidth), height(aHeight)
		{
			frame_buffer = new unsigned char[width * height * 4];
			memset(frame_buffer, 255, width * height * 4 * sizeof(unsigned char));
		}

		void SetPixel(int posX, int posY, unsigned char r, unsigned char g, unsigned char b)
		{
			frame_buffer[(posY * width + posX) * 4 + 0] = r;
			frame_buffer[(posY * width + posX) * 4 + 1] = g;
			frame_buffer[(posY * width + posX) * 4 + 2] = b;
			frame_buffer[(posY * width + posX) * 4 + 3] = 255;
		}
	};
}

extern CPURenderer::ViewPort gViewPort;