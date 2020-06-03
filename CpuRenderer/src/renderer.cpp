#include "renderer.h"
#include <iostream>

void CPURenderer::ViewPort::DoNothing()
{
	std::cout << "DoNothing";
}

CPURenderer::ViewPort gViewPort(800, 600);