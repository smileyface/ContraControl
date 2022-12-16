#include <thread>
#include <functional>   // std::mem_fn
#include <algorithm>    // std::find

#include "../sys_interface/keyboard_interface.h"
#include "../action_layer/predefined_layer.h"

std::thread keyboard_thread;


Keyboard_Interface::Keyboard_Interface()
{ 
	active = false;
	keyboard_present = false;
}

Keyboard_Interface::~Keyboard_Interface()
{
}

bool is_simple = false;

bool Keyboard_Interface::keep_reading()
{
	bool val = active && keyboard_present;
	if(is_simple)
	{
		val = val && !Predefined_Action_Layer::Simple_Input_Layer::returned;
	}
	return val;
}

void Keyboard_Interface::loop()
{
	while(keep_reading())
		readEv();
}

void Keyboard_Interface::start_listening()
{
	if(keyboard_present)
	{
		active = true;
		keyboard_thread = std::thread([this] ()
									  {
										  this->loop();
									  });
	}
}

void Keyboard_Interface::stop_listening()
{
	if(keyboard_present)
	{
		active = false;
		if(keyboard_thread.joinable())
			keyboard_thread.join();
	}
}

bool Keyboard_Interface::get_keyboard_present()
{
	return keyboard_present;
}

std::string Keyboard_Interface::get_simple()
{
	std::string val;
	action_stack.change_action_layers(Predefined_Action_Layer::SIMPLE_BUFFERED_INPUT_LAYER);
	is_simple = true;
	while(!Predefined_Action_Layer::Simple_Input_Layer::terminated)
	{

	}

    val = input_buffer.get_buffer();
	Predefined_Action_Layer::Simple_Input_Layer::returned = true;
	return val;
}