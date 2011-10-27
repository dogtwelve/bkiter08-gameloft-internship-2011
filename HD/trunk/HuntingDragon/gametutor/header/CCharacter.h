#ifndef __CCHARACTER_H__
#define __CCHARACTER_H__

#include "CModel.h"
#include "CObject.h"
#include "CCamera.h"
#include "CThirdPersonCamera.h"

#define START_FRAME 0
#define END_FRAME 1

#define NUM_ACTIONS 4
enum ECharacterAction { ACTION_STAND, ACTION_RUN, ACTION_ATTACK, ACTION_DIE };

class CCharacter: public CObject, public CModel
{
public:
	CCharacter();
	virtual ~CCharacter();

	void Init();
	void Update();
	void Render(Matrix*);
	void Release();
	void LoadActions(const char* strCfgName);	

private:
	ECharacterAction m_CurAction; // current action of character
	__UINT32 m_iCurFrames;
	/*
		m_Frames[action][START_FRAME]: start frame
		m_Frames[action][END_FRAME]: end frame
	*/
	__UINT32 m_Frames[NUM_ACTIONS][2];
	CCamera m_Camera;
	float xangle;
};

#endif