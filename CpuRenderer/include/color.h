#pragma once

namespace CPURenderer
{
	struct Color
	{
		static const Color red, green, blue, black, yellow, sky_blue;
		unsigned char r, g, b, a = 255;
	};
}