#include "../keyboard_buffer_input.h"

#include <string>

Keyboard_Interface* Keyboard_Buffer_Input::keyboard;
#ifdef _WIN32
#include <Windows.h>
#include "../sys_interface/windows_keyboard.h"
#endif
#ifdef __linux__
#include "../sys_interface/linux_keyboard.h"
//#include "system_interfaces/linux_network_interface.h"
#endif

Keyboard_Buffer_Input::Keyboard_Buffer_Input():
	block(false),
	timed_out(false)
{
#ifdef _WIN32
	Keyboard_Buffer_Input::keyboard = new Windows_Keyboard();
#endif
#ifdef __linux__
	Keyboard_Buffer_Input::keyboard = new Linux_Keyboard();
#endif
}

std::string Keyboard_Buffer_Input::get_input()
{
	timed_out = false;
	return keyboard->get_simple();
}

int Keyboard_Buffer_Input::get_number()
{
	std::string string_to_number = get_input();
	int val;
	if(string_to_number == "")
	{
		timed_out = true;
		val = -1;
	}
	else
	{
		val = stoi(get_input());
	}
	return val;
}

bool Keyboard_Buffer_Input::get_timed_out()
{
	return timed_out;
}