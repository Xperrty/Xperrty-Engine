#include "xppch.h"
#include "Vector3.h"

namespace Xperrty {
	inline float Vector3::magnitude()
	{
		return sqrt(x * x + y * y +z*z);
	}
	void Vector3::normalize()
	{
		operator/(magnitude());
	}
	Vector3& Vector3::operator+(float other)
	{
		x += other;
		y += other;
		z += other;
		return *this;
	}
	Vector3& Vector3::operator+(const Vector3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}
	Vector3& Vector3::operator-(float other)
	{
		x -= other;
		y -= other;
		z -= other;
		return *this;
	}
	Vector3& Vector3::operator-(const Vector3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}
	Vector3& Vector3::operator/(float other)
	{
		x /= other;
		y /= other;
		z /= other;
		return *this;
	}
	Vector3& Vector3::operator/(const Vector3& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}
	Vector3& Vector3::operator*(float other)
	{
		x *= other;
		y *= other;
		z *= other;
		return *this;
	}
	Vector3& Vector3::operator*(const Vector3& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}
}