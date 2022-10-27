#include "xppch.h"
#include "Vector2.h"
#include <math.h>
namespace Xperrty {
	inline float Vector2::magnitude()
	{
		//TODO: Maybe cache the result?
		return sqrt(x * x + y * y);
	}
	void Vector2::normalize()
	{
		operator/(magnitude());
	}
	Vector2 Vector2::zero()
	{
		return Vector2(0,0);
	}
	Vector2& Vector2::operator+(float other)
	{
		x += other;
		y += other;
		return *this;
	}
	Vector2& Vector2::operator+(const Vector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	Vector2& Vector2::operator-(float other)
	{
		x -= other;
		y -= other;
		return *this;
	}
	Vector2& Vector2::operator-(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}
	Vector2& Vector2::operator/(float other)
	{
		x /= other;
		y /= other;
		return *this;
	}
	Vector2& Vector2::operator/(const Vector2& other)
	{
		x /= other.x;
		y /= other.y;
		return *this;
	}
	Vector2& Vector2::operator*(float other)
	{
		x *= other;
		y *= other;
		return *this;
	}
	Vector2& Vector2::operator*(const Vector2& other)
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}
}