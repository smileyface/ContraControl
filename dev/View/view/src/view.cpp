#include "../../view/console_format/console_view.h"

#include "../../input_interface/sys_interface/windows_keyboard.h"
#include "../../input_interface/sys_interface/linux_keyboard.h"

Console_View::Console_View()
{ 
	keyboard = Keyboard_Buffer_Input();
}