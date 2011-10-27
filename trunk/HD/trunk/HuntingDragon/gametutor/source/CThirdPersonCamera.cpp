#include "CThirdPersonCamera.h"

CThirdPersoncamera::CThirdPersoncamera()
	:m_fObjDistance(3.0f), m_fCameraHeight(4.0f), m_Obj(NULL)
{
	m_Up = Vector3(1, 0, 0);
}

CThirdPersoncamera::~CThirdPersoncamera()
{
}

void CThirdPersoncamera::Update()
{
	float radius = sqrt(m_fObjDistance * m_fObjDistance - m_fCameraHeight * m_fCameraHeight);
	m_RelativeEyePos = Vector3(0, radius, m_fCameraHeight);
}

void CThirdPersoncamera::FixToObject(CObject* obj)
{
	m_Obj = obj;
}

void CThirdPersoncamera::BuildViewMatrix()
{
	if(m_Obj != NULL)
	{
		//m_EyePos = m_RelativeEyePos.MultipleByMatrix(m_Obj->GetWorldMatrix());
		/*Vector eye = Vector(m_RelativeEyePos[0], m_RelativeEyePos[1], m_RelativeEyePos[2], 0);

		eye = m_Obj->GetWorldMatrix().MultVector(eye);
		float* data = eye.GetData();
		m_EyePos = Vector3(data[0], data[1], data[2]);*/

		m_EyePos = m_Obj->GetPosition() + Vector3(0, 0, m_fCameraHeight);
		//m_EyePos = Vector3(0, 0, m_fCameraHeight);
		//m_Up = m_Obj->GetDirection();
		//m_Lookat = m_Obj->GetPosition() - m_EyePos;
		m_Lookat = Vector3(0, 0, -1);

		CCamera::BuildViewMatrix();
	}
}