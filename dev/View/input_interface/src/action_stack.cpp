#include "../action_layer/action_stack.h"
#include "../action_layer/predefined_layer.h"

Action_Stack::Action_Stack()
{

}

Action_Layer* Action_Stack::get_active_layer()
{
	return active_layer;
}

void Action_Stack::change_action_layers(int layer)
{
	if(active_layer != 0)
		active_layer->transition_from();
	active_layer = &layers[layer];
	active_layer->transition_to();
}

void Action_Stack::setup_action_layers()
{ 
	layers.emplace_back(Predefined_Action_Layer::buffered_input_layer());
	change_action_layers(0);
}

int Action_Stack::add_action_layer()
{
	layers.emplace_back(Action_Layer());
	return layers.size() - 1;
}