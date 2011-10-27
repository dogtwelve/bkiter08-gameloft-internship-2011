#ifndef __GAMETUTOR_H__
#define __GAMETUTOR_H__

#include "Header.h"
#include "CDevice.h"
#include "CFpsController.h"
#include "CGame.h"
#include "Config.h"
#include "CState.h"
#include "CStateManagement.h"
#include "CViewController.h"
#include "CVSView.h"
#include "SGameConfig.h"
#include "Stream.h"


#if CONFIG_PLATFORM==PLATFORM_WIN32_VS
#	pragma comment(lib, "gametutor.lib")
#endif

using namespace GameTutor;

#endif