#pragma once

namespace CPURenderer
{
	struct Vector4
	{
		float x, y, z, w;
	};

	// we implement it in row major
	struct Matrix4
	{
		float mat[4][4];
		static const Matrix4 identity, zero;

		Matrix4 operator+(const Matrix4& rhs) const;
		Matrix4 operator-(const Matrix4& rhs) const;
		Matrix4 operator*(const Matrix4& rhs) const;
		Vector4 operator*(const Vector4& rhs) const;
	};
}