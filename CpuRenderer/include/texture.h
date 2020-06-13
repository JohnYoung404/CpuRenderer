#pragma once
#include <lodepng.h>
#include "color.h"

namespace CPURenderer
{
	class Texture
	{
	public:
		bool load(const std::string &filePath);
		unsigned width() const { return _width; }
		unsigned height() const { return _height; }
		Color getPixel(float xCoord, float yCoord) const;

	private:
		std::vector<unsigned char> _image;
		unsigned _width, _height;
	};
}
