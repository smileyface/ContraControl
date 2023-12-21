#include "../keyboard_buffer_input.h"

#include <string>

#ifdef _WIN32
#include <Windows.h>
#include "../sys_interface/windows_keyboard.h"
#endif
#ifdef __linux__
#include "../sys_interface/linux_keyboard.h"
//#include "system_interfaces/linux_network_interface.h"
#endif

Keyboard_Buffer_Input::Keyboard_Buffer_Input()
{
	block = false;
#ifdef _WIN32
	keyboard = new Windows_Keyboard();
#endif // _WIN32

#ifdef __linux__
	keyboard = new Linux_Keyboard();
#endif
	keyboard->initalize();
}

std::string Keyboard_Buffer_Input::get_input()
{
	return std::string();
}

int Keyboard_Buffer_Input::get_number()
{
	return 0;
}

bool Keyboard_Interface::get_keyboard_present() const
{
	return keyboard_present;
}