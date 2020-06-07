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

			CalViewMat();
		}

		void CalViewMat()
		{
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

		void yaw(float angle)
		{
			float cs = (float)cos(angle * M_PI / 180);
			float sn = (float)sin(angle * M_PI / 180);

			Vector3 t = n;
			Vector3 s = u;

			n = t * cs - s * sn;
			u = t * sn + s * cs;
		}

		void pitch(float angle)
		{
			float cs = (float)cos(angle * M_PI / 180);
			float sn = (float)sin(angle * M_PI / 180);

			Vector3 t = v;
			Vector3 s = n;

			v = t * cs - s * sn;
			n = t * sn + s * cs;
		}

		void slide(float du, float dv, float dn)
		{
			eye.x += du * u.x + dv * v.x + dn * n.x;
			eye.y += du * u.y + dv * v.y + dn * n.y;
			eye.z += du * u.z + dv * v.z + dn * n.z;
			at.x += du * u.x + dv * v.x + dn * n.x;
			at.y += du * u.y + dv * v.y + dn * n.y;
			at.z += du * u.z + dv * v.z + dn * n.z;
		}

		float getDist()
		{
			float dist = (float)(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2));
			return (float)pow(dist, 0.5);
		}

		void RotateX(float angle)
		{
			float d = getDist();
			int cnt = 100;
			float theta = angle / cnt;
			float slide_d = (float)(2 * d * sin(theta * 3.14159265 / 360));
			yaw(theta / 2);
			for (; cnt != 0; --cnt)
			{
				slide(slide_d, 0, 0);
				yaw(theta);
			}
			yaw(-theta / 2);
		}

		void RotateY(float angle)
		{
			float d = getDist();
			int cnt = 100;
			float theta = angle / cnt;
			float slide_d = (float)(2 * d *sin(theta * 3.14159265 / 360));
			pitch(theta / 2);
			for (; cnt != 0; --cnt)
			{
				slide(0, -slide_d, 0);
				pitch(theta);
			}
			pitch(-theta / 2);
		}
	};
}