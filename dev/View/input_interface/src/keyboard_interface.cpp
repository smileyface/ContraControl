#include <thread>

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
	keyboard_thread = std::thread([this]
								  {
									  this->loop();
								  });
}
