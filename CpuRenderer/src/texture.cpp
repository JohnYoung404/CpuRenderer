#include <cmath>
#include <iostream>
#include "texture.h"

bool CPURenderer::Texture::load(const std::string &filePath)
{
	unsigned int errcode = lodepng::decode(_image, _width, _height, filePath);
	if (errcode)
	{
		std::cout << "encoder error " << errcode << ": " << lodepng_error_text(errcode) << std::endl;
		return false;
	}
	return true;
}

CPURenderer::Color CPURenderer::Texture::getPixel(float sCoord, float tCoord) const
{
	float floatingS = sCoord - trunc(sCoord);
	float floatingT = tCoord - trunc(tCoord);
	size_t _sPos = (size_t)((floatingS >= 0 ? floatingS : (1.0f + floatingS)) * (_width - 1));
	size_t _tPos = (size_t)((floatingT >= 0 ? floatingT : (1.0f + floatingT)) * (_height - 1));
	Color ret;
	ret.r = _image[(_sPos* _width + _tPos) * 4];
	ret.g = _image[(_sPos* _width + _tPos) * 4 + 1];
	ret.b = _image[(_sPos* _width + _tPos) * 4 + 2];
	ret.a = _image[(_sPos* _width + _tPos) * 4 + 3];
	return ret;
}
