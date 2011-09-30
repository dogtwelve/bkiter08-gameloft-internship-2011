#pragma once
#ifndef __VECTOR3_H__
#define __VECTOR3_H__

class Vector3
{
public:
	Vector3(void);
	Vector3(float _x, float _y, float _z): x(_x), y(_y), z(_z) {}
	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
	float setX(float x) { this->x = x; }
	float setY(float y) { this->y = y; }
	float setZ(float z) { this->z = z; }

	static float DotProduct(Vector3 & a, Vector3 & b);
	static Vector3 CrossProduct(Vector3 & a, Vector3 & b);

	virtual ~Vector3(void);

private:
	float x, y, z;
};

#endif