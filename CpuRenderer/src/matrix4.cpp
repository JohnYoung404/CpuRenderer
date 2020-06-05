#include "matrix4.h"

const CPURenderer::Matrix4 CPURenderer::Matrix4::zero = {};
const CPURenderer::Matrix4 CPURenderer::Matrix4::identity = 
{
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
};