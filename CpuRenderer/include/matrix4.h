#pragma once
#include <string>
#include "vector3.h"

namespace CPURenderer
{
	struct Vector4
	{
		union 
		{
			struct
			{
				float x, y, z, w;
			};
			float _arr[4];
		};
	};

	// we implement it in row major
	struct Matrix4
	{
		float mat[4][4];
		static const Matrix4 identity, zero;

		Matrix4 operator+(const Matrix4 &rhs) const;
		Matrix4 operator-(const Matrix4 &rhs) const;
		Matrix4 operator*(const Matrix4 &rhs) const;
		Vector4 operator*(const Vector4 &vec4) const;
		Vector3 operator*(const Vector3 &vec3) const;
		Matrix4 inverse() const;
		Matrix4 transpose() const;
		float det() const;
	};

	inline Matrix4 operator*(const Matrix4 &mat4, float scalar)
	{
		Matrix4 ret;
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				ret.mat[i][j] = mat4.mat[i][j] * scalar;
		return ret;
	}

	inline Matrix4 operator*(float scalar, const Matrix4 &mat4)
	{
		Matrix4 ret;
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				ret.mat[i][j] = mat4.mat[i][j] * scalar;
		return ret;
	}

	inline Matrix4 CPURenderer::Matrix4::operator+(const Matrix4 &rhs) const
	{
		Matrix4 ret;
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				ret.mat[i][j] = mat[i][j] + rhs.mat[i][j];
		return ret;
	}

	inline Matrix4 CPURenderer::Matrix4::operator-(const Matrix4 &rhs) const
	{
		Matrix4 ret;
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				ret.mat[i][j] = mat[i][j] - rhs.mat[i][j];
		return ret;
	}

	inline Matrix4 Matrix4::operator*(const Matrix4 &rhs) const
	{
		Matrix4 ret = Matrix4::zero;;
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				for (int k = 0; k < 4; ++k)
					ret.mat[i][j] += mat[i][k] * rhs.mat[k][j];
		return ret;
	}

	//row major matrix, so we should place vector in right hand side.
	inline Vector4 Matrix4::operator*(const Vector4 &vec4) const
	{
		Vector4 ret = {0, 0, 0, 0};
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				ret._arr[i] += vec4._arr[j] * mat[i][j];
		return ret;
	}

	inline Vector3 Matrix4::operator*(const Vector3 &vec3) const
	{
		Vector4 extended = { vec3.x, vec3.y, vec3.z, 1.0f };
		Vector4 product = (*this) * extended;
		return Vector3{product.x / product.w, product.y / product.w , product.z / product.w };
	}

	inline Matrix4 Matrix4::transpose() const
	{
		Matrix4 ret;
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				ret.mat[i][j] = mat[j][i];
		return ret;
	}
}