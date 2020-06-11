#pragma once
#include "vector3.h"
#include "vertex.h"

namespace CPURenderer
{
namespace Math
{
	enum LerpAxis
	{
		X, Y, Z
	};

	// lerp of two vectors by giving one dimension value.
	inline Vector3 VectorLerp(const Vector3& from, const Vector3& to, float val, LerpAxis axis)
	{
		Vector3 gap = to - from;
		float scalar;
		switch (axis)
		{
		case CPURenderer::Math::X:
			scalar = (val - from.x) / gap.x;
			break;
		case CPURenderer::Math::Y:
			scalar = (val - from.y) / gap.y;
			break;
		case CPURenderer::Math::Z:
			scalar = (val - from.z) / gap.z;
			break;
		default:
			break;
		}
		Vector3 ret = from + scalar * gap;
		return  ret;
	}

	inline Vertex VertexLerp(const Vertex& from, const Vertex& to, float val, LerpAxis axis)
	{
		// temporarily only deal with positions.
		return Vertex{ VectorLerp(from.pos, to.pos, val, axis), VectorLerp(from.norm, to.norm, val, axis) };
	}
}
}