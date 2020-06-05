#pragma once
#include <string>
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
					ret.mat[i][j] += mat[k][j] * rhs.mat[i][k];
		return ret;
	}

	//row major matrix, so we should place vector in right hand side.
	inline Vector4 Matrix4::operator*(const Vector4 &vec4) const
	{
		Vector4 ret = {0, 0, 0, 0};
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				ret._arr[i] += vec4._arr[j] * mat[j][i];
		return ret;
	}

	inline Matrix4 Matrix4::inverse() const
	{
		return Matrix4();
	}

	inline Matrix4 Matrix4::transpose() const
	{
		return Matrix4();
	}

	inline float Matrix4::det() const
	{
		return 0.0f;
	}
}