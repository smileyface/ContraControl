#include <thread>
#include <functional>   // std::mem_fn

#include "../sys_interface/keyboard_interface.h"
std::thread keyboard_thread;

Keyboard_Interface::Keyboard_Interface()
{ }

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

void Keyboard_Interface::set_on_press(KPI key, std::function<void()> func)
{
	for(auto& it : code_map)
	{
		if(it.second == key)
		{
			it.second.on_press = func;
			return;
		}
	}
}

void Keyboard_Interface::set_on_release(KPI key, std::function<void()> func)
{ 
	for(auto& it : code_map)
	{
		if(it.second == key)
		{
			it.second.on_release = func;
			return;
		}
	}
}