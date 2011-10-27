#include "CCamera.h"

void CCamera::Lookat(Vector3 eye, Vector3 pos, Vector3 up)
{
	m_EyePos = eye;
	m_Lookat = pos - eye;
	m_Up = up;
}

void CCamera::Lookat(
	float eyex, float eyey, float eyez,
	float posx, float posy, float posz,
	float upx, float upy, float upz)
{
	m_EyePos = Vector3(eyex, eyey, eyez);
	m_Lookat = Vector3(posx - eyex, posy - eyey, posz - eyez);
	m_Up = Vector3(upx, upy, upz);
}

void CCamera::Perspective(float fovy, float aspect, float zNear, float zFar)
{
	m_matProjection.LoadIdentity();
	m_matProjection.Perspective(fovy, aspect, zNear, zFar);
}

void CCamera::Ortho(float left, float right, float top, float bottom, float near, float far)
{
	m_matProjection.LoadIdentity();
	m_matProjection.Ortho(left, right, top, bottom, near, far);
}

void CCamera::BuildViewMatrix()
{
	Vector3 pos = m_EyePos + m_Lookat;
	m_matView.LoadIdentity();
	m_matView.LookAt(
		m_EyePos[0], m_EyePos[1], m_EyePos[2],
		pos[0], pos[1], pos[2],
		m_Up[0], m_Up[1], m_Up[2]
	);
}

Matrix CCamera::GetViewMatrix()
{
	return m_matView;
}

Matrix CCamera::GetProjMatrix()
{
	return m_matProjection;
}

Matrix CCamera::GetViewProjMatrix()
{
	return m_matProjection * m_matView;
}