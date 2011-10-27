#ifndef __CVSVIEW_H__
#define __CVSVIEW_H__

#include "Header.h"
#include "CSingleton.h"
#if (CONFIG_PLATFORM==PLATFORM_WIN32_VS)

namespace GameTutor
{
	class CVSView: public CAbsSingleton<CVSView>
	{
	public:
		CVSView(__INT32 w, __INT32 h, bool fullscreen = false, const char*name = 0);
		virtual ~CVSView();
		void Update();
		void UpdateView();
		static void Render(ESContext* esContext);
		static void OnTouchDown(ESContext* esContext, int x, int y);
		static void OnTouchUp(ESContext* esContext, int x, int y);
		static void OnTouchMove(ESContext* esContext, WPARAM wparam, int x, int y);
		static void KeyFunc(ESContext* esContext, unsigned char key, int x, int y);
		static void KeyUpFunc(ESContext* esContext, unsigned char key);

		__INT32 GetWidth() {return m_iWidth;}
		__INT32 GetHeight() {return m_iHeight;}
		__INT32 IsFullScreen() {return m_isFullScreen;}
		
		void SetContext(ESContext* esContext);
		void RefreshOpenGL();
		void StartMainLoop();
		
	private:
		ESContext* esContext;
		__INT32 m_iWidth;
		__INT32 m_iHeight;
		bool m_isFullScreen;
		char *m_strTitle;
		void Destroy();	

		bool m_isLeftMouseDown;
		bool m_isKeyDown;
	};
}

#endif //(CONFIG_PLATFORM==PLATFORM_WIN32_VS)
#endif