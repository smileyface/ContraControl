#include "../../view/console_format/console_view.h"

#include "../../input_interface/sys_interface/windows_keyboard.h"
#include "../../input_interface/sys_interface/linux_keyboard.h"

Console_View::Console_View()
{ 
#ifdef _WIN32
	keyboard = new Windows_Keyboard();
#endif
#ifdef __linux__
	keyboard = new Linux_Keyboard();
#endif
}

View::View() :
	quiter(false)
{ }

View::~View()
{ }

void View::quit_view()
{ 
	quiter = true;
}
