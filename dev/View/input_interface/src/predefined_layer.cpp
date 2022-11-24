#include "../action_layer/predefined_layer.h"
#include <vector>

std::vector<std::pair<KPI, KEY_STATE>> buffer;
bool block;
bool loop_it;

Action_Layer Predefined_Action_Layer::buffered_input_layer()
{
	Action_Layer new_layer;
	new_layer.transition_to = [&new_layer] () mutable
	{
		buffer.clear();
		for(std::pair<const int, KPI> i : new_layer.get_codemap())
		{
			new_layer.set_on_press(i.second, [i] () mutable
									{
										buffer.push_back(std::make_pair(i.second, KEY_STATE::PRESSED));
									});
			new_layer.set_on_release(i.second, [i] () mutable
										{
											buffer.push_back(std::make_pair(i.second, KEY_STATE::RELEASED));
										});
		}
	};

	new_layer.transition_from = [&new_layer] () mutable
	{
		for(auto i : new_layer.get_codemap())
		{
			new_layer.set_on_press(i.second, [] ()
								   { });
			new_layer.set_on_release(i.second, [] ()
									 { });
		}
	};
	return new_layer;
}