#pragma once

namespace CPURenderer
{
	struct ViewPort
	{
		int width, height;
		unsigned char *frame_buffer;

		ViewPort(int aWidth, int aHeight) : width(aWidth), height(aHeight) 
		{
			frame_buffer = new unsigned char[width * height * 3];
			for (int i = 0; i < width; ++i)
			{
				for (int j = 0; j < height; ++j)
				{
					frame_buffer[(i * height + j) * 3 + 0] = 255;	//R
					frame_buffer[(i * height + j) * 3 + 1] = 255;	//G
					frame_buffer[(i * height + j) * 3 + 2] = 0;	//B
				}
			}
		}
		~ViewPort()
		{
			delete[] frame_buffer;
		}

		void DoNothing();
	};

	extern ViewPort gViewPort;
}
