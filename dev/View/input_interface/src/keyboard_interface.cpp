#include <thread>
#include <functional>   // std::mem_fn
#include <algorithm>    // std::find

#include "../sys_interface/keyboard_interface.h"
std::thread keyboard_thread;


Keyboard_Interface::Keyboard_Interface()
{ 
	active = false;
	keyboard_present = false;
}

Keyboard_Interface::~Keyboard_Interface()
{
}

void Keyboard_Interface::loop()
{
	while(active && keyboard_present)
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
		keyboard_thread.join();
	}
}

bool Keyboard_Interface::get_keyboard_present()
{
	return keyboard_present;
}