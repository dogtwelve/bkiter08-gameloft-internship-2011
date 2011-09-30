#pragma once
#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <math.h>
#ifndef PI
#define PI 3.14159
#endif
#define DEG_2_RAD (PI/360.0f)
#define RAD_2_DEG (360.0f/PI)

#include "Vector3.h"

class Matrix
{
public:
	/* static methods */
	/* projection */
	static Matrix Perspective(float left, float right, float bottom, float top, float near, float far);
	static Matrix PerspectiveFov(float fovy, float aspect, float znear, float zfar);
	static Matrix Ortho(float left, float right, float bottom, float top, float near, float far);

	/* tranformation */
	static Matrix RotationX(float angle);
	static Matrix RotationY(float angle);

	/* view */
	static Matrix LookAt(Vector3 eye, Vector3 center, Vector3 up);
	static Matrix LookAt(float eyex, float eyey, float eyez,
		float centerx, float centery, float centerz,
		float upx, float upy, float upz);

	/* other operation */
	static Matrix Multiply(Matrix& a, Matrix& b);	
public:
	Matrix(void);
	Matrix(float m[4][4]);
	virtual ~Matrix(void);

	void LoadIdentity();
	void MakeTranspose();
	float* ToArray();
private: 
	float m[4][4];
};

#endif