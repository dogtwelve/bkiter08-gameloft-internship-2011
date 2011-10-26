
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

	//CReaderStream<CFileWin32Driver> file("dragoon.pcx");
	m_img = CImage::LoadPCX("dragoon.pcx");
	m_img->BindGPU(m_pVideoDriver);

	m_text = new CText2D("GAMELOFT INTERNSHIP!");

	m_Monster = new CModel();
	m_Monster->LoadModel("dragoon.md2");	
	zAngle = 0;
}

void CStateLogo::Update()
{
	mat.LoadIdentity();
	mat.Perspective(45, 4.0f/3.0f, 1.0f, 100.0f);
	mat.LookAt(2, 0, 0,
		0, 0, 0,
		0, 0, 1);
	mat.Rotate(zAngle, 0, 0, 1);
	zAngle++;
}

void CStateLogo::OnControllerEvent(SControllerEvent Event)
{
	switch(Event.PointerData.Event) 
	{
	case EPE_PRESSED:
		printf("mouse clicked!\n");
		break;
	case EPE_RELEASED:
		printf("mouse released!\n");
		break;
	case EPE_DRAGGED:
		printf("mouse dragged!\n");
		break;
	}
}

void CStateLogo::Render()
{		
	g->Clear(SColor<float>(0, 0, 0, 1));
	static int nFrames = 40;
	g3d->SetMVPMatrix(mat.GetData());
	m_Monster->Render(nFrames++);
	if(nFrames >= 46) nFrames = 40;
	Sleep(100);
	//Sleep(500);
	//g3d->DrawTriangle(CVertexPT(1, 0, 0, 1, 0), CVertexPT(0, 0, 0, 0, 0), CVertexPT(1, 1, 2, 1, 1), m_img);
	g3d->Flush();


	//g->DrawImageRegion(SRect<float>(-1, -1, 1, 1), SRect<float>(0, 0, 1, 1), m_img);
	//m_text->Render(0, 100);
	g->Flush();
	//Log("State Logo: %d Fps = %d FrameDT = %d", m_iCount, CFpsController::GetInstance()->GetRuntimeFps(), CFpsController::GetInstance()->GetFrameDt());
}

void CStateLogo::Exit()
{
	Log("State Logo: Exit");
}
