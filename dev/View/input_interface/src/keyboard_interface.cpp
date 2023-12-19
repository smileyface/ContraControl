#include <algorithm>    // std::find
#include <condition_variable>
#include <functional>   // std::mem_fn
#include <iostream>
#include <stdint.h>
#include <thread>

#include "../action_layer/predefined_layer.h"
#include "../sys_interface/keyboard_interface.h"
#include "Messaging/message_relay.h"

std::thread keyboard_thread;
unsigned int BUFFERED_TIMEOUT = 5;

std::mutex cv_m;

std::condition_variable cv;

Keyboard_Interface::Keyboard_Interface()
{
	active = false;
	keyboard_present = false;
}

Keyboard_Interface::~Keyboard_Interface()
{ }

void Keyboard_Interface::initalize()
{ 
	initalize_codes();
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

bool Keyboard_Interface::get_keyboard_present() const
{
	return keyboard_present;
}

std::string Keyboard_Interface::get_simple()
{
	std::string val;
	action_stack.change_action_layers(Predefined_Action_Layer::SIMPLE_BUFFERED_INPUT_LAYER);
	//Spin while the buffer collects input

	std::unique_lock<std::mutex> lk(cv_m);
	if(cv.wait_until(lk, std::chrono::system_clock::now() + std::chrono::seconds(BUFFERED_TIMEOUT), [] ()
	   {
		   return Predefined_Action_Layer::Simple_Input_Layer::terminated == true;
	   }))
	{
		LOG_INFO("Terminated string recieved", "Keyboard Test Interface");
	}
	else
	{
		LOG_ERROR("No input recived", "Keyboard Test Interface");
	}

	val = input_buffer.get_buffer();
	Predefined_Action_Layer::Simple_Input_Layer::returned = Predefined_Action_Layer::Simple_Input_Layer::terminated;
	return val;
}