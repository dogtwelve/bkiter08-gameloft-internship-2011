#ifndef __CSTATELOGO_H__
#define __CSTATELOGO_H__

#include "gametutor.h"
#include "CImage.h"
#include "CGraphics2D.h"
#include "CGraphics3D.h"
#include "CGLPipelineDriver.h"
#include "CText2D.h"
#include "CModel.h"

using namespace GameTutor;

class CStateLogo: public CState
{
public:
	CStateLogo();
	~CStateLogo() { delete m_Monster; }

	void Init();
	void Update();
	void Render();
	void Exit();
	void OnControllerEvent(SControllerEvent Event);
private:
	__INT32 m_iCount;
	CImage *m_img;
	CGraphics2D *g;
	CGraphics3D *g3d;
	CGLPipelineDriver *m_pVideoDriver;
	CText2D* m_text;
	CModel* m_Monster;
	Matrix mat;
	int zAngle;
};
#endif