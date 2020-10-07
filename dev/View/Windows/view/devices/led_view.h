#include "../view.h"

class LED_View : public View
{
	LED_View(const char CLASS_NAME[], const char WIN_TEXT[], int nCmdShow)
	{
		initalize(CLASS_NAME, WIN_TEXT, nCmdShow);
	};
};