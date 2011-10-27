#include "gametutor.h"
#include "CExample.h"

int main()
{
#if CONFIG_PLATFORM==PLATFORM_WIN32_VS
	ESContext esContext;

	esInitContext(&esContext);
	esCreateWindow(
		&esContext, 
		"Hunting Dragon", 
		800, 600,
		ES_WINDOW_RGB
		);	

	esRegisterDrawFunc(&esContext, CVSView::Render);
	esRegisterKeyFunc(&esContext, CVSView::KeyFunc);
	esRegisterKeyUpFunc(&esContext, CVSView::KeyUpFunc);
	esRegisterTouchDownFunc(&esContext, CVSView::OnTouchDown);
	esRegisterTouchUpFunc(&esContext, CVSView::OnTouchUp);
	esRegisterTouchMoveFunc(&esContext, CVSView::OnTouchMove);

#endif


	SGameConfig cnf = {
		800,
		600,
		false,
		"Hello",
		new CExample(),
#if CONFIG_PLATFORM==PLATFORM_WIN32_VS
		&esContext
#endif
	};

	GameTutor::StartApp(cnf);	
}