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

Action_Layer* Keyboard_Interface::get_active_layer()
{
	return active_layer;
}

void Keyboard_Interface::stop_listening()
{
	if(keyboard_present)
	{
		active = false;
		keyboard_thread.join();
	}
}

void Keyboard_Interface::change_action_layers(int layer)
{ 
	if(active_layer != 0)
		active_layer->transition_from();
	active_layer = &layers[layer];
	active_layer->transition_to();
}

void Keyboard_Interface::setup_action_layers()
{
	layers.emplace_back(Predefined_Action_Layer::buffered_input_layer());
	change_action_layers(0);
}