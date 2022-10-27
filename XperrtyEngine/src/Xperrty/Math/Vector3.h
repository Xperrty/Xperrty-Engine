#pragma once
namespace Xperrty {

class Vector3
{
public:
	float x, y, z;
	Vector3(float x, float y, float z) :x(x), y(y), z(z) {}
	Vector3() :x(0), y(0), z(0) {}

	inline float magnitude();
	void normalize();

	Vector3& operator+(float other);
	Vector3& operator+(const Vector3& other);
	Vector3& operator-(float other);
	Vector3& operator-(const Vector3& other);
	Vector3& operator/(float other);
	Vector3& operator/(const Vector3& other);
	Vector3& operator*(float other);
	Vector3& operator*(const Vector3& other);

private:

};

}
