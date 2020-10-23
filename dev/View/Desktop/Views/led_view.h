#include "view.h"

class LED_View : public Desktop_View
{
	LED_View(const char CLASS_NAME[], const char WIN_TEXT[], int nCmdShow)
	{
		initalize(CLASS_NAME, WIN_TEXT, nCmdShow);
	};
};