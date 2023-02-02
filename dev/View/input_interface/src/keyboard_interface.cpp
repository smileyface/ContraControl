#include <thread>
#include <functional>   // std::mem_fn
#include <algorithm>    // std::find
#include <stdint.h>

#include "../sys_interface/keyboard_interface.h"
#include "../action_layer/predefined_layer.h"
#include "Messaging/message_relay.h"

std::thread keyboard_thread;
unsigned int BUFFERED_TIMEOUT = 5;

Keyboard_Interface::Keyboard_Interface() :
	keyboard_timeout_timer(1000),
	active(false),
	keyboard_present(false)
{ 
}

Keyboard_Interface::~Keyboard_Interface()
{
}

bool is_simple = false;


void Keyboard_Interface::loop()
{
	while(active && keyboard_present)
	{
		if(!Predefined_Action_Layer::Simple_Input_Layer::returned)
		{
			readEv();
		}
	}
	keyboard_timeout_timer.join();
	LOG_DEBUG("Reading loop over");
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

bool Keyboard_Interface::get_active()
{
	return active;
}

std::string Keyboard_Interface::get_simple()
{
	std::string val;
	action_stack.change_action_layers(Predefined_Action_Layer::SIMPLE_BUFFERED_INPUT_LAYER);
	//Spin while the buffer collects input
	keyboard_timeout_timer.start_clock();
	while(!keyboard_timeout_timer.get_alarm() && !Predefined_Action_Layer::Simple_Input_Layer::terminated)
	{
		keyboard_timeout_timer.update_time();

	}
	if(Predefined_Action_Layer::Simple_Input_Layer::terminated)
	{
		keyboard_timeout_timer.stop_clock();
	}

    val = input_buffer.get_buffer();
	Predefined_Action_Layer::Simple_Input_Layer::returned = Predefined_Action_Layer::Simple_Input_Layer::terminated &&
		!keyboard_timeout_timer.get_alarm();
	return val;
}