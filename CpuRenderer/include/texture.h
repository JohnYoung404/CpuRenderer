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
		Color getPixel(float sCoord, float tCoord) const
		{
			float floatingS = sCoord - (int)(sCoord);
			float floatingT = tCoord - (int)(tCoord);
			size_t _sPos = (size_t)((floatingS >= 0 ? floatingS : (1.0f + floatingS)) * (_width - 1));
			size_t _tPos = (size_t)((floatingT >= 0 ? floatingT : (1.0f + floatingT)) * (_height - 1));
			Color ret;
			ret.r = _image[(_sPos* _width + _tPos) * 4];
			ret.g = _image[(_sPos* _width + _tPos) * 4 + 1];
			ret.b = _image[(_sPos* _width + _tPos) * 4 + 2];
			ret.a = _image[(_sPos* _width + _tPos) * 4 + 3];
			return ret;
		}

	private:
		std::vector<unsigned char> _image;
		unsigned _width, _height;
	};
}
