#pragma once
#include "vector3.h"

namespace CPURenderer
{
	class Vertex
	{
	public:
		Vector3 pos;
		float xTexCoord, yTexCoord;
		float one_div_w;
		Vector3 norm;
	};
}