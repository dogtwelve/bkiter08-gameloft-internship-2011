
#include "CStateLogo.h"
#include "CStatePoster.h"
#include "SGraphics.h"
#include "CGraphics2D.h"

CStateLogo::CStateLogo():m_iCount(0), CState()
{

}

void CStateLogo::Init()
{
	Log("State Logo: Init");
	m_pVideoDriver = CGLPipelineDriver::GetInstance();
	g3d = CGraphics3D::GetInstance();
	g3d->Reset();

	g = CGraphics2D::GetInstance();
	g->Reset();

	

	m_text = new CText2D("GAMELOFT INTERNSHIP!");

	// init main chacracter
	m_MainCharacter = new CCharacter();
	m_MainCharacter->LoadModel("dragoon.md2");
	m_MainCharacter->LoadActions("dragoon.cfg");

	m_Enermy = new CCharacter();
	m_Enermy->LoadModel("dragoon.md2");
	m_Enermy->LoadActions("dragoon.cfg");

	// init camera
	m_ThirdPersonCamera = new CThirdPersoncamera();
	m_ThirdPersonCamera->FixToObject(m_MainCharacter);
	m_ThirdPersonCamera->Perspective(45, 4.0f/3.0f, 1.0f, 100.0f);

	// init terrain 
	m_Terrain = new CTerrain();
}

void CStateLogo::Update()
{		
	CControllerEventManager::GetInstance()->Update();
	m_MainCharacter->Update();	
	m_Enermy->Update();

	// update camera
	// third person camera

	m_ThirdPersonCamera->Update();
	m_ThirdPersonCamera->BuildViewMatrix();
}

void CStateLogo::OnControllerEvent(SControllerEvent Event)
{	
	switch(Event.Type)
	{
	/*case ECE_KEY:
		{
			CControllerKeyManager* keyMan = CControllerKeyManager::GetInstance();		
			if(keyMan->WasKeyPressed(EKEY_WIN_W))
			{
				printf("Key W pressed\n");
				m_MainCharacter->SetDirection(1.0f, 0, 0);
			}
			if(keyMan->WasKeyPressed(EKEY_WIN_S))
			{
				printf("Key S pressed\n");
				m_MainCharacter->SetDirection(-1.0f, 0, 0);
			}
		}
		break;*/
	case ECE_POINTER:
		{
			CControllerPointerManager* pointerManager = CControllerPointerManager::GetInstance();
			__INT32 numActives;
			SPointerUserInfo info[2];
			pointerManager->GetActivePointer(2, numActives, info);

			for(int i = 0; i < numActives; i++) 
			{
				SPointerUserInfo* pInfo = &info[i];
				SPosition2D<float> oglPos;
				CCoordinateConverter::WindowsToOpenGL(pInfo->CurrentPosition, oglPos);
				Vector3 dir = Vector3(oglPos.Y, -oglPos.X, 0.0f);				
				m_MainCharacter->SetDirection(dir);
			}
		}
		break;
	}
}

void CStateLogo::Render()
{		
	g->Clear(SColor<float>(0, 0, 0, 1));

	Matrix vpMat = m_ThirdPersonCamera->GetViewProjMatrix();
	Matrix world = m_MainCharacter->GetWorldMatrix();
	

	m_MainCharacter->Render(&vpMat);
	m_Enermy->Render(&vpMat);
		
	// draw terrain
	g3d->SetMVPMatrix(vpMat.GetData());	
	m_Terrain->Render();
	g3d->Flush();



	//m_text->Render(0, 100);
	g->Flush();
	//Log("State Logo: %d Fps = %d FrameDT = %d", m_iCount, CFpsController::GetInstance()->GetRuntimeFps(), CFpsController::GetInstance()->GetFrameDt());
}

void CStateLogo::Exit()
{
	Log("State Logo: Exit");

	m_MainCharacter->Release();
	m_Enermy->Release();

	delete m_Enermy;
	delete m_MainCharacter;
	delete m_Terrain;
	delete m_ThirdPersonCamera;
}
