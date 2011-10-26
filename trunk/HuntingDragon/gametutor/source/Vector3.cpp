#include <math.h>

#include "Vector3.h"

using namespace std;


Vector3::Vector3() {

}

Vector3::Vector3(float x, float y, float z) {
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

float &Vector3::operator[](int index) {
	return v[index];
}

float Vector3::operator[](int index) const {
	return v[index];
}

Vector3 Vector3::operator*(float scale) const {
	return Vector3(v[0] * scale, v[1] * scale, v[2] * scale);
}

Vector3 Vector3::operator/(float scale) const {
	return Vector3(v[0] / scale, v[1] / scale, v[2] / scale);
}

Vector3 Vector3::operator+(const Vector3 &other) const {
	return Vector3(v[0] + other.v[0], v[1] + other.v[1], v[2] + other.v[2]);
}

Vector3 Vector3::operator-(const Vector3 &other) const {
	return Vector3(v[0] - other.v[0], v[1] - other.v[1], v[2] - other.v[2]);
}

Vector3 Vector3::operator-() const {
	return Vector3(-v[0], -v[1], -v[2]);
}

const Vector3 &Vector3::operator*=(float scale) {
	v[0] *= scale;
	v[1] *= scale;
	v[2] *= scale;
	return *this;
}

const Vector3 &Vector3::operator/=(float scale) {
	v[0] /= scale;
	v[1] /= scale;
	v[2] /= scale;
	return *this;
}

const Vector3 &Vector3::operator+=(const Vector3 &other) {
	v[0] += other.v[0];
	v[1] += other.v[1];
	v[2] += other.v[2];
	return *this;
}

const Vector3 &Vector3::operator-=(const Vector3 &other) {
	v[0] -= other.v[0];
	v[1] -= other.v[1];
	v[2] -= other.v[2];
	return *this;
}

float Vector3::magnitude() const {
	return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

float Vector3::magnitudeSquared() const {
	return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
}

Vector3 Vector3::normalize() const {
	float m = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	return Vector3(v[0] / m, v[1] / m, v[2] / m);
}

float Vector3::dot(const Vector3 &other) const {
	return v[0] * other.v[0] + v[1] * other.v[1] + v[2] * other.v[2];
}

Vector3 Vector3::cross(const Vector3 &other) const {
	return Vector3(v[1] * other.v[2] - v[2] * other.v[1],
		v[2] * other.v[0] - v[0] * other.v[2],
		v[0] * other.v[1] - v[1] * other.v[0]);
}

Vector3 operator*(float scale, const Vector3 &v) {
	return v * scale;
}

ostream &operator<<(ostream &output, const Vector3 &v) {
	cout << '(' << v[0] << ", " << v[1] << ", " << v[2] << ')';
	return output;
}