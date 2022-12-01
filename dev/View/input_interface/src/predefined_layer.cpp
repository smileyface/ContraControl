#include "../action_layer/predefined_layer.h"
#include <vector>
#include <map>

bool block;
bool loop_it;

Action_Layer Predefined_Action_Layer::buffered_input_layer()
{
	Action_Layer new_layer;
	for(std::pair<const int, KPI> i : master_code_map)
	{
		new_layer.set_on_press(i.second, [i] () mutable
								{
									input_buffer.add(i.second, KEY_STATE::PRESSED);
								});
		new_layer.set_on_release(i.second, [i, &new_layer] () mutable
								{
									 input_buffer.add(i.second, KEY_STATE::RELEASED);
								});
	}
	return new_layer;
}