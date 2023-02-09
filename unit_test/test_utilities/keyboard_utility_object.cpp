#include "system_utilities.h"

#include "keyboard_interface_utilities.h"

#include "../../dev/View/input_interface/sys_interface/windows_keyboard.h"
#include "../../dev/View/input_interface/sys_interface/linux_keyboard.h"

#include "../../dev/View/input_interface/keyboard_buffer_input.h"

#include "../../dev/View/input_interface/action_layer/predefined_layer.h"

system_utilities::keyboard_utilities::Keyboard::Keyboard()
{
	system_utilities::keyboard_utilities::setup();
	buffer = 0;
	if(system_utilities::keyboard_utilities::connect == false)
	{
		buffer = new Test_Keyboard_Interface();
	}
	else if(system_utilities::WINDOWS)
	{
	#ifdef _WIN32
		buffer = new Windows_Keyboard();
	#endif // _WIN32
	}
	else if(system_utilities::LINUX)
	{
	#ifdef __linux__
		buffer = new Linux_Keyboard();
	#endif
	}
}

system_utilities::keyboard_utilities::Keyboard::~Keyboard()
{
	buffer->stop_listening();
	system_utilities::keyboard_utilities::tear_down();
}

void system_utilities::keyboard_utilities::Keyboard::wait_for_first_key(KPI key)
{

}


void system_utilities::keyboard_utilities::Keyboard::operator<<(const std::string& input)
{
	for(char i : input)
	{
		system_utilities::keyboard_utilities::press_button(i);
	}

	system_utilities::keyboard_utilities::press_button(system_utilities::keyboard_utilities::get_char_from_kpi(KEY::ENTER));
}

void system_utilities::keyboard_utilities::Keyboard::operator<<(const int& input)
{
	operator<<(std::to_string(input));
}

void system_utilities::keyboard_utilities::Keyboard::operator<<(const char& input)
{
	LOG_DEBUG(std::to_string(input) + " sent");
	system_utilities::keyboard_utilities::press_button(input);
}

void system_utilities::keyboard_utilities::Keyboard::set_key_operation(KPI key, std::function<void()> func)
{
	buffer->action_stack.get_active_layer()->set_on_press(key, func);
}

bool system_utilities::keyboard_utilities::Keyboard::keyboard_present()
{
	return buffer->get_keyboard_present();
}

bool system_utilities::keyboard_utilities::Keyboard::still_running()
{
	return !Predefined_Action_Layer::Simple_Input_Layer::terminated;
}

Keyboard_Interface* system_utilities::keyboard_utilities::Keyboard::get_interface()
{
	return buffer;
}

void system_utilities::keyboard_utilities::Keyboard::operator<(KPI key)
{
	buffer->action_stack.get_active_layer()->handle_event(key, 1);
	buffer->action_stack.get_active_layer()->handle_event(key, 0);
}

void system_utilities::keyboard_utilities::Keyboard::override_interface(Keyboard_Interface* new_interface)
{ 
	buffer = new_interface;
}
