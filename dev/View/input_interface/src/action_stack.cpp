#include "../action_layer/action_stack.h"
#include "../action_layer/predefined_layer.h"

Action_Stack::Action_Stack() :
	active_layer(0)
{
}

Action_Stack::~Action_Stack()
{
	active_layer = 0;
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
	layers[Predefined_Action_Layer::BUFFERED_INPUT_LAYER] = Predefined_Action_Layer::buffered_input_layer();
	layers[Predefined_Action_Layer::SIMPLE_BUFFERED_INPUT_LAYER] = Predefined_Action_Layer::simple_buffered_input_layer();
	last_id = Predefined_Action_Layer::END_OF_PREDEFINED;
	change_action_layers(Predefined_Action_Layer::BUFFERED_INPUT_LAYER);
}

int Action_Stack::add_action_layer()
{
	last_id++;
	layers[last_id] = Action_Layer();
	return last_id;
}



