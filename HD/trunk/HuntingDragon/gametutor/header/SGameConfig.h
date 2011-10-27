#ifndef __SGAMECONFIG_H__
#define __SGAMECONFIG_H__

#include "Header.h"
#include "CGame.h"

namespace GameTutor
{
	typedef struct _SGameConfig
	{
		__UINT16 iWidth;
		__UINT16 iHeight;
		bool isUseFullScreen;
		const char *strTitle;
		CGame* pGame;
#if CONFIG_PLATFORM==PLATFORM_WIN32_VS
		ESContext* esContext;
#endif
	}SGameConfig;
}

#endif