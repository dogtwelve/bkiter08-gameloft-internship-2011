#ifndef __CSTATEPOSTER_H__
#define __CSTATEPOSTER_H__

#include "gametutor.h"

class CStatePoster :public CState
{
public:
	CStatePoster();
	~CStatePoster() {}
	
	void Init();
	void Update();
	void Render();
	void Exit();
	void OnControllerEvent(SControllerEvent Event);

private:
	__INT32 m_iCount;
};

#endif