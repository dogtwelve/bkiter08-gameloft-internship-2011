#ifndef __CTHIRDPERSONCAMERA_H__
#define __CTHIRDPERSONCAMERA_H__

#include "CCamera.h"
#include "CObject.h"

class CThirdPersoncamera: public CCamera
{
public:
	CThirdPersoncamera();
	virtual ~CThirdPersoncamera();
	void Update();
	void FixToObject(CObject* obj);
	void BuildViewMatrix();
private:
	float m_fObjDistance; // distance to object
	float m_fCameraHeight;
	CObject* m_Obj;
	Vector3 m_RelativeEyePos;
};

#endif