#ifndef __COBJECT_H__
#define __COBJECT_H__

#include "Vector3.h"
#include "Matrix.h"
#include "Header.h"

class CObject
{
public:
	CObject() {};
	virtual ~CObject() {};

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Release() = 0;
	virtual void Render(Matrix* vpMatrix) = 0;

	void SetDirection(float x, float y, float z) { m_vecDir = Vector3(x, y, z); }
	void SetDirection(Vector3 dir) { m_vecDir = dir; }

	Matrix GetWorldMatrix() { return m_matWorld; }
	Vector3 GetPosition() { return m_Position; }
	Vector3 GetDirection() { return m_vecDir; }
	Vector3 GetNormal() { return m_vecNormal; }
protected:
	Vector3 m_Position;
	__UINT32 m_Velocity;
	Vector3 m_Acceleration;

	Vector3 m_vecNormal; // normal vector
	Vector3 m_vecDir; // direct of object

	Matrix m_matWorld;
};

#endif