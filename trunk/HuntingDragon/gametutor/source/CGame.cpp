#include "CGame.h"
#include "Header.h"
#include "CStateManagement.h"
#include "CDevice.h"
#include "CFpsController.h"
#include "CViewController.h"

namespace GameTutor
{
	CGame::CGame(): m_eStatus(EGSTATUS_INIT)
	{
		SetInstance(this);
	}

	void CGame::Pause()
	{
		m_eStatus = EGSTATUS_PAUSED;
	}

	void CGame::Resume()
	{
		m_eStatus = EGSTATUS_RUNNING;
	}

	void CGame::Exit()
	{
		m_eStatus = EGSTATUS_EXIT;
	}

	void CGame::Update()
	{
		switch (m_eStatus)
		{
		case EGSTATUS_INIT:
			this->Init();
			m_eStatus = EGSTATUS_RUNNING;
			break;
		case EGSTATUS_RUNNING:
		case EGSTATUS_PAUSED:
			CFpsController::GetInstance()->BeginCounter();
			CStateManagement::GetInstance()->Update(m_eStatus == EGSTATUS_PAUSED);
			CFpsController::GetInstance()->EndCounter();
			break;
		case EGSTATUS_EXIT:
			//force clean up current state
			CStateManagement::GetInstance()->SwitchState(0);
			CStateManagement::GetInstance()->Update(false);
			Destroy();
			break;
		default:
			break;
		}
	}

	void CGame::SetEvent(SControllerEvent Event)
	{
		CControllerEventManager::GetInstance()->OnEvent(Event);
		if (!this->OnControllerEvent(Event))
		{
			CState* state = CStateManagement::GetInstance()->GetCurrentState();
			if (state)
			{
				state->OnControllerEvent(Event);
			}
		}
	}
}