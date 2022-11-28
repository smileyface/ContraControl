#include "../action_layer/action_layer.h"

Keyboard_Code_Map master_code_map;

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

void Action_Layer::handle_event(int code, int event_value)
{ 
	int index = -1;
	for(auto i : code_map)
	{
		if(i.second.get_code() == code)
		{
			index = i.first;
			break;
		}
	}
	if(index >= 0)
	{
		code_map[index] = event_value;
	}
}


void Action_Layer::transition_from()
{

}

void Action_Layer::transition_to()
{

}