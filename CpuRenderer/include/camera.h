#pragma once
#include <cmath>
#include "vector3.h"
#include "matrix4.h"

namespace CPURenderer
{
	class Camera
	{
	private:
		Matrix4 _ViewMat;
		Matrix4 _ProjMat;

	public:
		Vector3 eye, up, at;
		Vector3 n, u, v;	// z, x, y

		Camera() = default;

		const Matrix4& ViewMat() const { return _ViewMat; }
		const Matrix4& ProjMat() const { return _ProjMat; }

		void LookAt(const Vector3 &a_eye, const Vector3 &a_up, const Vector3 &a_at)
		{
			eye = a_eye;
			up = a_up;
			at = a_at;

			// left-handed coordinate system
			n = (at - eye).normalize();
			u = cross(up, n).normalize();
			v = cross(n, u);

			_ViewMat.mat[0][0] = u.x;	_ViewMat.mat[0][1] = u.y;	_ViewMat.mat[0][2] = u.z;	_ViewMat.mat[0][3] = -dot(u, eye);
			_ViewMat.mat[1][0] = v.x;	_ViewMat.mat[1][1] = v.y;	_ViewMat.mat[1][2] = v.z;	_ViewMat.mat[1][3] = -dot(v, eye);
			_ViewMat.mat[2][0] = n.x;	_ViewMat.mat[2][1] = n.y;	_ViewMat.mat[2][2] = n.z;	_ViewMat.mat[2][3] = -dot(n, eye);
			_ViewMat.mat[3][0] = 0;		_ViewMat.mat[3][1] = 0;		_ViewMat.mat[3][2] = 0;		_ViewMat.mat[3][3] = 1;
		}
		
		//fovy: field of view in y direction.
		//aspect: aspect radio, defined as view width divided by height.
		//zn: Z-value of the near view plane.
		//zf: Z-value of the far view plane.
		void Project(float fovy, float aspect, float zn, float zf)
		{
			float yScale = 1.0f / tan(fovy * M_PI / 360.0f);
			float xScale = yScale / aspect;

			_ProjMat = Matrix4::zero;
			_ProjMat.mat[0][0] = xScale;
			_ProjMat.mat[1][1] = yScale;
			_ProjMat.mat[2][2] = zf / (zf - zn);
			_ProjMat.mat[2][3] = zn * zf / (zn - zf);
			_ProjMat.mat[3][2] = 1.0f;
		}
	};
}