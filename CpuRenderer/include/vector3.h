#pragma once
#include <cmath>

namespace CPURenderer
{
	struct Vector3
	{
		float x, y, z;
		static const Vector3 indentity, zero;

		Vector3 operator+(const Vector3& rhs) const { return Vector3{x + rhs.x, y + rhs.y, z + rhs.z}; }
		Vector3 operator-(const Vector3& rhs) const { return Vector3{ x - rhs.x, y - rhs.y, z - rhs.z }; }

		Vector3& add(const Vector3& rhs);
		Vector3& sub(const Vector3& rhs);
		Vector3& div(const Vector3& rhs);
		Vector3& cross(const Vector3& rhs);
		Vector3& normalize();
		float dot(const Vector3& rhs) const;
	};

	inline Vector3 cross(const Vector3& lhs, const Vector3& rhs)
	{ 
		return Vector3{ lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x };
	}

	inline float dot(const Vector3& lhs, const Vector3& rhs)
	{ 
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z; 
	}


	inline Vector3 operator*(const Vector3 vec, float scalar)
	{ 
		return Vector3{ vec.x * scalar, vec.y * scalar, vec.z * scalar };
	}

	inline Vector3 operator*(float scalar, const Vector3 vec)
	{
		return Vector3{ vec.x * scalar, vec.y * scalar, vec.z * scalar };
	}

	inline Vector3& Vector3::add(const Vector3& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	inline Vector3& Vector3::sub(const Vector3& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	inline Vector3& Vector3::div(const Vector3& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
		return *this;
	}

	inline Vector3& Vector3::cross(const Vector3& rhs)
	{
		float x_t = y * rhs.z - z * rhs.y;
		y = z * rhs.x - x * rhs.z;
		z = x * rhs.y - y * rhs.x;
		x = x_t;
		return *this;
	}

	inline Vector3& Vector3::normalize()
	{
		float scarlar = sqrt(x * x + y * y + z * z);
		x /= scarlar;
		y /= scarlar;
		z /= scarlar;
		return *this;
	}

	inline float Vector3::dot(const Vector3& rhs) const
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}
}