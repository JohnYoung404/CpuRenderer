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
	inline std::pair<Vector3, float> VectorLerp(const Vector3& from, const Vector3& to, float val, LerpAxis axis)
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
		return  std::make_pair(ret, scalar);
	}

	inline Vertex VertexLerp(const Vertex& from, const Vertex& to, float val, LerpAxis axis)
	{
		// temporarily only deal with positions.
		Vertex ret;
		const auto& retPair = VectorLerp(from.pos, to.pos, val, axis);
		ret.pos = retPair.first;
		float scalar = retPair.second;
		ret.norm = from.norm + scalar * (to.norm - from.norm);
		ret.sTexCoord = from.sTexCoord + scalar * (to.sTexCoord - from.sTexCoord);
		ret.tTexCoord = from.tTexCoord + scalar * (to.tTexCoord - from.tTexCoord);
		ret.one_div_w = from.one_div_w + scalar * (to.one_div_w - from.one_div_w);
		return ret;
	}
}
}