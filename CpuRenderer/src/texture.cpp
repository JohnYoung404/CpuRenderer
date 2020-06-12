#include <cmath>
#include <iostream>
#include "texture.h"

bool CPURenderer::Texture::load(const std::string &filePath)
{
	unsigned errcode = lodepng::decode(_image, _width, _height, filePath);
	if (errcode)
	{
		std::cout << "encoder error " << errcode << ": " << lodepng_error_text(errcode) << std::endl;
		return false;
	}
	return true;
}

CPURenderer::Color CPURenderer::Texture::getPixel(float xCoord, float yCoord) const
{
	size_t _xPos = (size_t)(abs(xCoord - trunc(xCoord)) * (_width - 1));
	size_t _yPos = (size_t)(abs(yCoord - trunc(yCoord)) * (_height - 1));
	Color ret;
	ret.r = _image[(_yPos * _width + _xPos) * 4];
	ret.g = _image[(_yPos * _width + _xPos) * 4 + 1];
	ret.b = _image[(_yPos * _width + _xPos) * 4 + 2];
	ret.a = _image[(_yPos * _width + _xPos) * 4 + 3];
	return ret;
}
