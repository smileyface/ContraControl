#include "../console_view.h"

#include "../../../input_interface/sys_interface/linux_keyboard.h"
#include "../../../input_interface/sys_interface/windows_keyboard.h"

Console_View::Console_View()
{
#ifdef _WIN32
	keyboard = new Windows_Keyboard();
#endif
#ifdef __linux__
	keyboard = new Linux_Keyboard();
#endif
	keyboard->initalize();
}

Console_View::~Console_View()
{
	delete keyboard;
}

void Console_View::on_create()
{
	View::on_create();
}

void Console_View::on_destroy()
{ 
	View::on_destroy();
}
