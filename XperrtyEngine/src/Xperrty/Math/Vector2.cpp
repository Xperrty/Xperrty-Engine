#include "xppch.h"
#include "Vector2.h"
#include <math.h>
namespace Xperrty {
	void Vector2::normalize()
	{
		float mag = magnitude();
		x = x /mag;
		y = y /mag;
	}
	Vector2 Vector2::zero()
	{
		return Vector2(0, 0);
	}
	Vector2 Vector2::operator+(float other)
	{
		return Vector2(x + other, y + other);

	}
	Vector2 Vector2::operator+(const Vector2& other)
	{
		return Vector2(x + other.x, y + other.y);
	}
	Vector2 Vector2::operator-(float other)
	{
		return Vector2(x - other, y - other);
		
	}
	Vector2 Vector2::operator-(const Vector2& other)
	{
		return Vector2(x - other.x, y - other.y);
	}
	Vector2 Vector2::operator/(float other)
	{
		return Vector2(x / other, y / other);
	}
	Vector2 Vector2::operator/(const Vector2& other)
	{
		return Vector2(x / other.x, y / other.y);
	}
	Vector2 Vector2::operator*(float other)
	{
		return Vector2(x * other, y * other);
	}
	Vector2 Vector2::operator*(const Vector2& other)
	{
		return Vector2(x * other.x, y * other.y);
	}
}