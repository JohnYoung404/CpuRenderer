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
