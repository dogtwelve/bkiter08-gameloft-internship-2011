#ifndef __CSTATELOGO_H__
#define __CSTATELOGO_H__

#include "gametutor.h"
#include "CImage.h"
#include "CGraphics2D.h"
#include "CGraphics3D.h"
#include "CGLPipelineDriver.h"
#include "CText2D.h"
#include "CModel.h"
#include "CCharacter.h"
#include "CCoordinateConverter.h"
#include "Header.h"
#include "CTerrain.h"

using namespace GameTutor;

class CStateLogo: public CState
{
public:
	CStateLogo();
	~CStateLogo() { }

	void Init();
	void Update();
	void Render();
	void Exit();
	void OnControllerEvent(SControllerEvent Event);
private:
	__INT32 m_iCount;
	
	CGraphics2D *g;
	CGraphics3D *g3d;
	CGLPipelineDriver *m_pVideoDriver;
	CText2D* m_text;
	//CModel* m_Monster;
	Matrix mat;
	int zAngle;
	int bzAngle;
	Vector3 eye;
	Vector3 baseEye;

	float Height, bHeight;

	CCharacter* m_MainCharacter;
	CCharacter* m_Enermy;
	
	CThirdPersoncamera* m_ThirdPersonCamera;

	CTerrain* m_Terrain;
};

#endif