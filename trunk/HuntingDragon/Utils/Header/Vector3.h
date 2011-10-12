#ifndef __VECTOR3_H__
#define __VECTOR3_H__

#include <iostream>

class Vector3 {
private:
	float v[3];
public:
	Vector3();
	Vector3(float x, float y, float z);

	float &operator[](int index);
	float operator[](int index) const;

	Vector3 operator*(float scale) const;
	Vector3 operator/(float scale) const;
	Vector3 operator+(const Vector3 &other) const;
	Vector3 operator-(const Vector3 &other) const;
	Vector3 operator-() const;

	const Vector3 &operator*=(float scale);
	const Vector3 &operator/=(float scale);
	const Vector3 &operator+=(const Vector3 &other);
	const Vector3 &operator-=(const Vector3 &other);

	float magnitude() const;
	float magnitudeSquared() const;
	Vector3 normalize() const;
	float dot(const Vector3 &other) const;
	Vector3 cross(const Vector3 &other) const;
};

Vector3 operator*(float scale, const Vector3 &v);
std::ostream &operator<<(std::ostream &output, const Vector3 &v);

#endif
