#pragma once
namespace Xperrty {

	class Vector2
	{
	public:
		float x, y;
		Vector2(float x, float y) :x(x), y(y) {}
		Vector2() :x(0), y(0) {}

		inline float magnitude();
		void normalize();

		static Vector2 zero();

		Vector2& operator+(float other);
		Vector2& operator+(const Vector2& other);
		Vector2& operator-(float other);
		Vector2& operator-(const Vector2& other);
		Vector2& operator/(float other);
		Vector2& operator/(const Vector2& other);
		Vector2& operator*(float other);
		Vector2& operator*(const Vector2& other);
	};
}

