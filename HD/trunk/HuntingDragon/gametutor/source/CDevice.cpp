#include "CDevice.h"
#include "CViewController.h"
#include "SGameConfig.h"

#if CONFIG_PLATFORM==PLATFORM_WIN32_VS
namespace GameTutor
{
	void CDevice::SleepEx(__UINT64 milisec)
	{
		Sleep(DWORD(milisec));
	}

	__UINT64 CDevice::GetTimer()
	{
		return clock();
	}

	void StartApp(SGameConfig cnf)
	{
		//init view
		CViewController<VIEWCLASS>::CreateView(cnf.iWidth, cnf.iHeight, cnf.isUseFullScreen, cnf.strTitle);
#if CONFIG_PLATFORM==PLATFORM_WIN32_VS
		CVSView::GetInstance()->SetContext(cnf.esContext);
		CViewController<VIEWCLASS>::GetInstance()->GetView()->UpdateView();
		CVSView::GetInstance()->StartMainLoop();		
#endif

		//CViewController<VIEWCLASS>::GetInstance()->GetView()->Update();
	}
}



#else // CONFIG_PLATFORM!=PLATFORM_WIN32_VS

namespace GameTutor
{
	CDevice* CDevice::s_pInstance = 0;

	void CDevice::SleepEx(__UINT64 milisec)
	{
		TODO("CDevice::SleepEx for CONFIG_PLATFORM!=PLATFORM_WIN32_VS is not implement yet !");
	}

	__UINT64 CDevice::GetTimer()
	{
		TODO(" CDevice::GetTimer for CONFIG_PLATFORM!=PLATFORM_WIN32_VS is not implement yet !");
		return 0;
	}
}
#endif


