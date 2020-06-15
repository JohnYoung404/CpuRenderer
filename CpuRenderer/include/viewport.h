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
		float* z_buffer;
		static ViewPort instance;

		ViewPort(const ViewPort &other) = delete;
		void operator=(const ViewPort& other) = delete;

		ViewPort(int aWidth, int aHeight) : width(aWidth), height(aHeight)
		{
			frame_buffer = new unsigned char[width * height * 4];
			z_buffer = new float[width * height];
			memset(frame_buffer, 255, width * height * 4 * sizeof(unsigned char));
			ZBufferClear();
		}

		~ViewPort()
		{
			delete[] frame_buffer;
			delete[] z_buffer;
		}

		void SetPixel(int posX, int posY, Color c)
		{
			if (posX < 0 || posX >= width || posY < 0 || posY >= height)
				//throw std::out_of_range("invalid viewport pixel index");
				//it seems without clipping is faster, so we dont regard out-of-range as an error here.
				return;

			frame_buffer[(posY * width + posX) * 4 + 0] = c.b;
			frame_buffer[(posY * width + posX) * 4 + 1] = c.g;
			frame_buffer[(posY * width + posX) * 4 + 2] = c.r;
			frame_buffer[(posY * width + posX) * 4 + 3] = c.a;
		}

		void SetPixelZCheck(int posX, int posY, Color c, float zVal)
		{
			if (posX < 0 || posX >= width || posY < 0 || posY >= height)
				return;

			if (z_buffer[posY * width + posX] < zVal)
				return;

			frame_buffer[(posY * width + posX) * 4 + 0] = c.b;
			frame_buffer[(posY * width + posX) * 4 + 1] = c.g;
			frame_buffer[(posY * width + posX) * 4 + 2] = c.r;
			frame_buffer[(posY * width + posX) * 4 + 3] = c.a;

			z_buffer[posY * width + posX] = zVal;
		}

		void ZBufferClear()
		{
			for (int i = 0; i < width; ++i)
				for (int j = 0; j < height; ++j)
					z_buffer[j * width + i] = FLT_MAX;
		}
	};
}