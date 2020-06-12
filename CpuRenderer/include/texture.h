#pragma once
#include <lodepng.h>
#include "color.h"

namespace CPURenderer
{
	class Texture
	{
	public:
		bool load(const std::string &filePath);
		size_t width() const { return _width; }
		size_t height() const { return _height; }
		Color getPixel(float xCoord, float yCoord) const;

	private:
		std::vector<unsigned char> _image;
		size_t _width, _height;
	};
}