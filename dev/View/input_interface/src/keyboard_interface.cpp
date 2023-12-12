#include <thread>
#include <functional>   // std::mem_fn
#include <algorithm>    // std::find
#include <iostream>
#include <stdint.h>

#include "../sys_interface/keyboard_interface.h"
#include "../action_layer/predefined_layer.h"
#include "Messaging/message_relay.h"

std::thread keyboard_thread;
unsigned int BUFFERED_TIMEOUT = 5;

Keyboard_Interface::Keyboard_Interface()
{
	active = false;
	keyboard_present = false;
}

Keyboard_Interface::~Keyboard_Interface()
{ }

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

std::string Keyboard_Interface::get_simple()
{
	std::string val;
	action_stack.change_action_layers(Predefined_Action_Layer::SIMPLE_BUFFERED_INPUT_LAYER);
	unsigned int counter = 1;
	unsigned int count_the_counter = 0;
	//Spin while the buffer collects input
	while(!Predefined_Action_Layer::Simple_Input_Layer::terminated)
	{
		if(counter == 0)
		{
			count_the_counter++;
			LOG_DEBUG("Waiting for input");
		}
		counter++;
		if(count_the_counter == BUFFERED_TIMEOUT)
		{
			LOG_ERROR("No input recived", "Keyboard Interface");
			break;
		}
	}

	val = input_buffer.get_buffer();
	Predefined_Action_Layer::Simple_Input_Layer::returned = Predefined_Action_Layer::Simple_Input_Layer::terminated;
	return val;
}