#include "CVSView.h"
#include "CGame.h"
#include "CDevice.h"
#include "CControllerEventManager.h"

#if (CONFIG_PLATFORM==PLATFORM_WIN32_VS)

namespace GameTutor
{
	void UpdateFunc(ESContext* esContext, float dt)
	{
		CGame* a = CGame::GetInstance();
		CGame::GetInstance()->Update();
		if (!CGame::GetInstance()->IsAlive())
		{
			CGame::GetInstance()->Exit();
			SendMessageA(esContext->hWnd, WM_CLOSE, 0, 0);
			//eglDestroyContext(esContext->eglDisplay, esContext->eglSurface);

			return;
		}
		eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
	}	

	//---------------------------------------------------------------------------
	// Constructor
	//---------------------------------------------------------------------------

	CVSView::CVSView(int w, int h, bool fullscreen, const char*name):m_iWidth(w), 
		m_iHeight(h), m_isFullScreen(false)
	{
		SetInstance(this);
		if (name)
		{
			m_strTitle = new char[strlen(name) + 1];
			strcpy(m_strTitle, name);
		}
		else
		{
			char *xname = "Hunting Dragon";
			m_strTitle = new char[strlen(xname) + 1];
			strcpy(m_strTitle, xname);
		}
	}

	void CVSView::Render(ESContext *esContext)
	{
		
	}

	void CVSView::OnTouchDown(ESContext* esContext, int x, int y)
	{
		SControllerEvent Event;
		// TODO: need to implement
		if (!CVSView::GetInstance()) return;
		CVSView::GetInstance()->m_isLeftMouseDown = true;
		Event.Type = ECE_POINTER;
		Event.PointerData.Event = EPE_PRESSED;
		Event.PointerData.ID = 0;
		Event.PointerData.X = x;
		Event.PointerData.Y = y;
		CGame::GetInstance()->SetEvent(Event);		
	}

	void CVSView::OnTouchUp(ESContext* esContext, int x, int y)
	{
		// TODO: need to implement
		SControllerEvent Event;
		if (!CVSView::GetInstance()) return;
		if (CVSView::GetInstance()->m_isLeftMouseDown)
		{
			CVSView::GetInstance()->m_isLeftMouseDown = false;
			Event.Type = ECE_POINTER;
			Event.PointerData.Event = EPE_RELEASED;
			Event.PointerData.ID = 0;
			Event.PointerData.X = x;
			Event.PointerData.Y = y;
			CGame::GetInstance()->SetEvent(Event);
		}		
	}

	void CVSView::OnTouchMove(ESContext* esContext, WPARAM wparam, int x, int y)
	{
		//TODO: need to implement
		SControllerEvent Event;
		if (!CVSView::GetInstance()) return;
		Event.Type = ECE_POINTER;
		Event.PointerData.ID = 0;
		if(wparam == MK_LBUTTON)
		{				
			Event.PointerData.Event = EPE_DRAGGED;
			Event.PointerData.X = x;
			Event.PointerData.Y = y;
			CGame::GetInstance()->SetEvent(Event);
		}
		else
		{
			if (CVSView::GetInstance()->m_isLeftMouseDown)
			{
				Event.PointerData.Event = EPE_RELEASED;					
				Event.PointerData.X = x;
				Event.PointerData.Y = y;
				CVSView::GetInstance()->m_isLeftMouseDown = false;
				CGame::GetInstance()->SetEvent(Event);
			}
		}
	}

	void CVSView::UpdateView()
	{		
		
	}

	void CVSView::RefreshOpenGL()
	{
		eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);		
	}

	void CVSView::SetContext(ESContext* esContext)
	{
		this->esContext = esContext;
	}

	void CVSView::StartMainLoop()
	{
		esRegisterUpdateFunc(esContext, UpdateFunc);
		esMainLoop(esContext);
	}

	//---------------------------------------------------------------------------
	// Destructor
	//---------------------------------------------------------------------------
	CVSView::~CVSView()
	{
		Destroy();
		delete m_strTitle;
	}

	
	//---------------------------------------------------------------------------
	// update win32 message
	//---------------------------------------------------------------------------
	void CVSView::Update()
	{
	
	}

	//---------------------------------------------------------------------------
	// Destroy win32 window
	//---------------------------------------------------------------------------
	void CVSView::Destroy()
	{
	}	
}

#endif