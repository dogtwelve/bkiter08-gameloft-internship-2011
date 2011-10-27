#ifndef __CCAMERA_H__
#define __CCAMERA_H__

#include "Vector3.h"
#include "Matrix.h"

class CCamera
{
public:
	CCamera() {};
	virtual ~CCamera() {};

	void Lookat(Vector3 eye, Vector3 pos, Vector3 up);
	void Lookat(
		float eyex, float eyey, float eyez,
		float posx, float posy, float posz,
		float upx, float upy, float upz
	);
	void Perspective(float fovy, float aspect, float zNear, float zFar);
	void Ortho(float left, float right, float top, float bottom, float near, float far);
	void BuildViewMatrix();
	
	Matrix GetViewMatrix();
	Matrix GetProjMatrix();
	Matrix GetViewProjMatrix();
protected:
	Vector3 m_EyePos;
	Vector3 m_Lookat;
	Vector3 m_Up;

	Matrix m_matProjection;
	Matrix m_matView;
};

#endif