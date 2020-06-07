#pragma once
#include <cmath>
#include "vector3.h"
#include "matrix4.h"

namespace CPURenderer
{
	class Camera
	{
	private:
		Matrix4 _viewMat;
		Matrix4 _projMat;
		Matrix4 _screenMappingMat;

	public:
		Vector3 eye, up, at;
		Vector3 n, u, v;	// z, x, y

		Camera() = default;

		const Matrix4& ViewMat() const { return _viewMat; }
		const Matrix4& ProjMat() const { return _projMat; }
		const Matrix4& ScrMappingMat() const { return _screenMappingMat; }

		void LookAt(const Vector3 &a_eye, const Vector3 &a_up, const Vector3 &a_at)
		{
			eye = a_eye;
			up = a_up;
			at = a_at;

			// left-handed coordinate system
			n = (at - eye).normalize();
			u = cross(up, n).normalize();
			v = cross(n, u);

			_viewMat.mat[0][0] = u.x;	_viewMat.mat[0][1] = u.y;	_viewMat.mat[0][2] = u.z;	_viewMat.mat[0][3] = -dot(u, eye);
			_viewMat.mat[1][0] = v.x;	_viewMat.mat[1][1] = v.y;	_viewMat.mat[1][2] = v.z;	_viewMat.mat[1][3] = -dot(v, eye);
			_viewMat.mat[2][0] = n.x;	_viewMat.mat[2][1] = n.y;	_viewMat.mat[2][2] = n.z;	_viewMat.mat[2][3] = -dot(n, eye);
			_viewMat.mat[3][0] = 0;		_viewMat.mat[3][1] = 0;		_viewMat.mat[3][2] = 0;		_viewMat.mat[3][3] = 1;
		}
		
		//fovy: field of view in y direction.
		//aspect: aspect radio, defined as view width divided by height.
		//zn: Z-value of the near view plane.
		//zf: Z-value of the far view plane.
		void Project(float fovy, float aspect, float zn, float zf)
		{
			float yScale = 1.0f / (float)tan(fovy * M_PI / 360.0f);
			float xScale = yScale / aspect;

			_projMat = Matrix4::zero;
			_projMat.mat[0][0] = xScale;
			_projMat.mat[1][1] = yScale;
			_projMat.mat[2][2] = zf / (zf - zn);
			_projMat.mat[2][3] = zn * zf / (zn - zf);
			_projMat.mat[3][2] = 1.0f;
		}

		void ScreenMapping(const ViewPort &viewPort)
		{
			_screenMappingMat = Matrix4::zero;
			_screenMappingMat.mat[0][0] = (viewPort.width - 1) / 2.0f;
			_screenMappingMat.mat[1][1] = (viewPort.height - 1) / 2.0f;
			_screenMappingMat.mat[2][2] = 1;
			_screenMappingMat.mat[0][3] = (viewPort.width - 1) / 2.0f;
			_screenMappingMat.mat[1][3] = (viewPort.height - 1) / 2.0f;
			_screenMappingMat.mat[3][3] = 1;
		}
	};
}