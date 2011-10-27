#ifndef __CEXAMPLE_H__
#define __CEXAMPLE_H__
#include "gametutor.h"

using namespace GameTutor;

class CExample:public CGame
{
public:
	CExample(): CGame() {}
	virtual ~CExample() {}

protected:
	void Init();
	void Destroy();
};

#endif