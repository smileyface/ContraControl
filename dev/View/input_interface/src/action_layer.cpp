#include "../action_layer/action_layer.h"
#include "../action_layer/predefined_layer.h"


Keyboard_Code_Map master_code_map;

Keyboard_Input_Buffer input_buffer;

Action_Layer::Action_Layer()
{
	code_map = {};
}

Action_Layer::~Action_Layer()
{

}

void Action_Layer::set_on_press(KPI key, Keyboard_Event func)
{
	auto found_key = code_map.find(key.index());
	if(found_key == code_map.end())
	{
		code_map[key.index()] = key;
		found_key = code_map.find(key.index());
	}
		
	found_key->second.on_press = func;
}

void Action_Layer::set_on_release(KPI key, Keyboard_Event func)
{
	auto found_key = code_map.find(key.index());
	if(found_key == code_map.end())
	{
		code_map[key.index()] = key;
		found_key = code_map.find(key.index());
	}

	found_key->second.on_release = func;
}

void Action_Layer::set_on_hold(KPI key, Keyboard_Event func)
{ 
	auto found_key = code_map.find(key.index());
	if(found_key == code_map.end())
	{
		code_map[key.index()] = key;
		found_key = code_map.find(key.index());
	}

	found_key->second.on_hold = func;
}

void Action_Layer::handle_event(KPI key, int event_value)
{ 
	code_map[key.index()] = event_value;
}


void Action_Layer::transition_from()
{

}

void Action_Layer::transition_to()
{
	Predefined_Action_Layer::Simple_Input_Layer::terminated = false;
	Predefined_Action_Layer::Simple_Input_Layer::returned = false;
	input_buffer.clear();
}

KEY_STATE Action_Layer::get_pressed_state(KPI key)
{
	return code_map[key.index()].get_state();
}