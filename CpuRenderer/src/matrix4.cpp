#include "matrix4.h"

const CPURenderer::Matrix4 CPURenderer::Matrix4::zero = {};
const CPURenderer::Matrix4 CPURenderer::Matrix4::identity = 
{
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
};

namespace CPURenderer
{
	namespace
	{
		// Calculate the determinant of a 3x3 sub-matrix.
		//     | A B C |
		// M = | D E F |   det(M) = A * (EI - HF) - B * (DI - GF) + C * (DH - GE)
		//     | G H I |
		// inline works cause we only use it in this file.
		inline float matrixDet3(const Matrix4 &m, int col0, int col1, int col2, int row0, int row1, int row2)
		{
			return m.mat[row0][col0] *
				(m.mat[row1][col1] * m.mat[row2][col2] -
					m.mat[row2][col1] * m.mat[row1][col2]) -
				m.mat[row0][col1] *
				(m.mat[row1][col0] * m.mat[row2][col2] -
					m.mat[row2][col0] * m.mat[row1][col2]) +
				m.mat[row0][col2] *
				(m.mat[row1][col0] * m.mat[row2][col1] -
					m.mat[row2][col0] * m.mat[row1][col1]);
		}
	}

	float Matrix4::det() const
	{
		float ret;
		ret =  mat[0][0] * matrixDet3(*this, 1, 2, 3, 1, 2, 3);
		ret -= mat[0][1] * matrixDet3(*this, 0, 2, 3, 1, 2, 3);
		ret += mat[0][2] * matrixDet3(*this, 0, 1, 3, 1, 2, 3);
		ret -= mat[0][3] * matrixDet3(*this, 0, 1, 2, 1, 2, 3);
		return ret;
	}

	// based on https://github.com/radekp/qt/blob/master/src/gui/math3d/qmatrix4x4.cpp
	Matrix4 Matrix4::inverse() const
	{
		Matrix4 ret;
		float _det = det();
		_det = 1.0f / _det;

		ret.mat[0][0] =  matrixDet3(*this, 1, 2, 3, 1, 2, 3) * _det;
		ret.mat[1][0] = -matrixDet3(*this, 0, 2, 3, 1, 2, 3) * _det;
		ret.mat[2][0] =  matrixDet3(*this, 0, 1, 3, 1, 2, 3) * _det;
		ret.mat[3][0] = -matrixDet3(*this, 0, 1, 2, 1, 2, 3) * _det;
		ret.mat[0][1] = -matrixDet3(*this, 1, 2, 3, 0, 2, 3) * _det;
		ret.mat[1][1] =  matrixDet3(*this, 0, 2, 3, 0, 2, 3) * _det;
		ret.mat[2][1] = -matrixDet3(*this, 0, 1, 3, 0, 2, 3) * _det;
		ret.mat[3][1] =  matrixDet3(*this, 0, 1, 2, 0, 2, 3) * _det;
		ret.mat[0][2] =  matrixDet3(*this, 1, 2, 3, 0, 1, 3) * _det;
		ret.mat[1][2] = -matrixDet3(*this, 0, 2, 3, 0, 1, 3) * _det;
		ret.mat[2][2] =  matrixDet3(*this, 0, 1, 3, 0, 1, 3) * _det;
		ret.mat[3][2] = -matrixDet3(*this, 0, 1, 2, 0, 1, 3) * _det;
		ret.mat[0][3] = -matrixDet3(*this, 1, 2, 3, 0, 1, 2) * _det;
		ret.mat[1][3] =  matrixDet3(*this, 0, 2, 3, 0, 1, 2) * _det;
		ret.mat[2][3] = -matrixDet3(*this, 0, 1, 3, 0, 1, 2) * _det;
		ret.mat[3][3] =  matrixDet3(*this, 0, 1, 2, 0, 1, 2) * _det;

		return ret;
	}
}