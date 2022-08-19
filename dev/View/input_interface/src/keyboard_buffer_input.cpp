#include "../keyboard_buffer_input.h"

#include <string>

#ifdef _WIN32
#include "../sys_interface/windows_input_interface.h"
#endif
#ifdef __linux__
#include "../sys_interface/linux_keyboard.h"
//#include "system_interfaces/linux_network_interface.h"
#endif

Keyboard_Buffer_Input::Keyboard_Buffer_Input()
{
#ifdef _WIN32
#include <conio.h>
#include <Windows.h>
	Keyboard_Interface* keyboard = new Windows_Keyboard();
#endif // _WIN32

#ifdef __linux__
	Keyboard_Interface* keyboard = new Linux_Keyboard();
#endif

}

std::string Keyboard_Buffer_Input::get_input()
{
	return std::string();
}

int Keyboard_Buffer_Input::get_number()
{
	return 0;
}

bool Keyboard_Interface::get_keyboard_present()
{
	return keyboard_present;
}