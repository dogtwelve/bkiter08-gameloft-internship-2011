#include "CStateManagement.h"

namespace GameTutor
{
	void CStateManagement::Update(bool isPause)
	{
		// check if need switch state
		if (m_pCurrentState != m_pNextState)
		{
			if (m_pCurrentState) 
			{
				m_pCurrentState->Exit();
				delete m_pCurrentState;
			}
			if (m_pNextState) 
			{
				m_pNextState->Init();
			}
			m_pCurrentState = m_pNextState;
		}

		//update state
		if (m_pCurrentState)
		{
			if (!isPause)
			{
				m_pCurrentState->Update();
			}
			m_pCurrentState->Render();
		}
	}

	void CStateManagement::SwitchState(CState* nextState)
	{
		m_pNextState = nextState;
	}
}