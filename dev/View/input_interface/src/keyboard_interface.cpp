#include <thread>
#include <functional>   // std::mem_fn
#include <algorithm>    // std::find
#include <iostream>
#include <stdint.h>

#include "../sys_interface/keyboard_interface.h"
#include "../action_layer/predefined_layer.h"
#include "Messaging/message_relay.h"

unsigned int BUFFERED_TIMEOUT = 5;

Keyboard_Interface::Keyboard_Interface() :
	keyboard_task()
{ 
	active = false;
	keyboard_present = false;
	Scheduler::get_instance()->add_system_task([this] ()
											   {
												   Keyboard_Interface::step();
											   });
	Scheduler::get_instance()->add_cleanup_task([] ()
												{ });
}

Keyboard_Interface::~Keyboard_Interface()
{
}

bool is_simple = false;


void Keyboard_Interface::loop()
{

	if(!Predefined_Action_Layer::Simple_Input_Layer::returned)
	{
		readEv();
	}
	LOG_DEBUG("Reading loop over");
}

void Keyboard_Interface::start_listening()
{
	if(keyboard_present)
	{
		active = true;
		keyboard_task.set_persistence(true);
		Scheduler::get_instance()->add_task(&keyboard_task);
		LOG_INFO("Adding Keyboard", "Keyboard Interface");
	}
}

void Keyboard_Interface::step()
{
	keyboard_task.add_subtask(Cleaned_Task([this] ()
							  {
								  loop();
							  }));
}

void Keyboard_Interface::stop_listening()
{
	if(keyboard_present)
	{
		active = false;
		keyboard_task.set_persistence(false);
		LOG_INFO("Removing Keyboard", "Keyboard Interface");
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
	unsigned int counter=1;
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