#pragma once
#include <SDL.h>
#include <string>
#include "color.h"

namespace CPURenderer
{
	struct ViewPort
	{
		int width, height;
		unsigned char* frame_buffer;
		static ViewPort instance;

		ViewPort(int aWidth, int aHeight) : width(aWidth), height(aHeight)
		{
			frame_buffer = new unsigned char[width * height * 4];
			memset(frame_buffer, 255, width * height * 4 * sizeof(unsigned char));
		}

		~ViewPort()
		{
			delete[] frame_buffer;
		}

		void SetPixel(int posX, int posY, Color c)
		{
			if (posX < 0 || posX > width || posY < 0 || posY > height)
				throw std::out_of_range("invalid viewport pixel index");

			frame_buffer[(posY * width + posX) * 4 + 0] = c.b;
			frame_buffer[(posY * width + posX) * 4 + 1] = c.g;
			frame_buffer[(posY * width + posX) * 4 + 2] = c.r;
			frame_buffer[(posY * width + posX) * 4 + 3] = c.a;
		}
	};
}