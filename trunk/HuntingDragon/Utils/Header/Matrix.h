#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <string.h>
#include <math.h>
#include "Vector3.h"

#define PI 3.1415926535897932384626433832795f
enum AXIS {X_AXIS, Y_AXIS, Z_AXIS};

class Vector
{
protected:
	float data[4];
public:
	Vector();
	Vector(float x, float y, float z, float w);
	Vector(float*);
	Vector operator = (const Vector);
	float* GetData();
	void Normalize();

};

class Matrix
{
protected:
	float data[4][4];
public:
	Matrix();
	Matrix(float*);

	/* operator */
	Matrix operator = (const Matrix);
	bool operator == (const Matrix);
	Matrix operator *(const Matrix M);
	void Multiply (const Matrix);
	void Multiply (float* data);	

	/* tranformation */
	void Translate(float x, float y, float z);
	void Rotate(float angle, AXIS axis);
	void Rotate(float angle, float x, float y, float z);
	void Scale(float x, float y, float z);

	/* viewing */
	void LookAt(float eyex, float eyey, float eyez, 
		float centerx, float centery, float centerz,
		float upx, float upy, float upz);

	/* projection */
	void Frustume(float left, float right, float bottom, float top, float near, float far);
	void Perspective(float fovy, float aspect, float nearZ, float farZ);
	void Ortho(float left, float right, float bottom, float top, float nearZ, float farZ);

	/* other */
	float* GetData();
	void LoadIdentity();
	void MakeTranspose();
	void Inverse();	
	bool Decompose_Pos_AngleZ(float &x, float &y, float &z, float &angle);
	Vector MultVector(Vector v);
};


#endif