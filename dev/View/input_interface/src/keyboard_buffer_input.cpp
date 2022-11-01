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
	loop_it = false;
#ifdef _WIN32
	keyboard = new Windows_Keyboard();
#endif // _WIN32

#ifdef __linux__
	keyboard = new Linux_Keyboard();
#endif

}

void Keyboard_Buffer_Input::setup_buffer()
{ 
	buffer.clear();
	loop_it = true;
	if(keyboard->get_keyboard_present())
	{
		for(std::pair<const int, KPI> i : keyboard->get_codemap())
		{
			if(i.second == KEY::ENTER)
			{
				keyboard->set_on_press(KEY::ENTER, [this] () mutable
									   {
										   loop_it = false;
									   });
			}
			keyboard->set_on_press(i.second, [this, i] () mutable
								   {
									   buffer.push_back(std::make_pair(i.second, KEY_STATE::PRESSED));
								   });
			keyboard->set_on_release(i.second, [this, i] () mutable
								   {
									   buffer.push_back(std::make_pair(i.second, KEY_STATE::RELEASED));
								   });
		}
	}
}

void Keyboard_Buffer_Input::teardown_buffer()
{
	for(auto i : keyboard->get_codemap())
	{
		keyboard->set_on_press(i.second, [] () { });
	}
}

void Keyboard_Buffer_Input::get_buffered_input()
{
	
	setup_buffer();
	if(keyboard->get_keyboard_present())
	{
		keyboard->start_listening();
		while(loop_it)
		{

		}
		keyboard->stop_listening();
	}
	teardown_buffer();
}

std::string Keyboard_Buffer_Input::get_input()
{
	std::string return_string = "";
	get_buffered_input();
	for(std::pair<KPI, KEY_STATE> i : buffer)
	{
		return_string += KPI_to_acsii(i);
	}
	return return_string;
}


#include <iostream>
#include <stdexcept>
int Keyboard_Buffer_Input::get_number()
{
	std::size_t pos {}; 
	std::string int_as_string = get_input();
	if(int_as_string == "")
	{
		int_as_string = "32767";
	}
	try
	{
		const int i { stoi(int_as_string, &pos) };
	}
	catch(std::invalid_argument const& ex)
	{
		std::cout << "std::invalid_argument::what(): " << ex.what() << '\n';
	}
	catch(std::out_of_range const& ex)
	{
		std::cout << "std::out_of_range::what(): " << ex.what() << '\n';
		const long long ll { std::stoll(int_as_string, &pos) };
		std::cout << "std::stoll('" << int_as_string << "'): " << ll << "; pos: " << pos << '\n';
	}
	return stoi(int_as_string, &pos);
}

bool Keyboard_Interface::get_keyboard_present()
{
	return keyboard_present;
}

std::map<int, KPI> Keyboard_Interface::get_codemap()
{
	return code_map;
}