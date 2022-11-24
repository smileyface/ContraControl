#include "../action_layer/action_layer.h"

Keyboard_Code_Map Action_Layer::code_map;

Action_Layer::Action_Layer()
{

}

Action_Layer::~Action_Layer()
{

}

void Action_Layer::set_on_press(KPI key, Keyboard_Event func)
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

void Action_Layer::set_on_release(KPI key, Keyboard_Event func)
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

void Action_Layer::add_code(int code, KPI key)
{ 
	code_map[code] = key;
}

void Action_Layer::handle_event(int code, int event_value)
{ 
	if(code_map.find(code) != code_map.end())
	{
		code_map[code] = event_value;
	}
}

Keyboard_Code_Map Action_Layer::get_codemap()
{
	return code_map;
}