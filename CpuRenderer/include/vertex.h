#pragma once
#include "vector3.h"

namespace CPURenderer
{
	class Vertex
	{
	public:
		Vector3 pos;
		Vector3 norm;
		float xTexCoord, yTexCoord;
	};
}