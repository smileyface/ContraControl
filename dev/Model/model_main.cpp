#include "model_main.h"

#include "Logging/logging.h"
#include "Interfaces/types/state.h"


Timer model_timer;

Node_Map model::nodes;
bool model::model_running = true;

Command_List model::step_actions;

Node_Id model::my_node_id;


void model::initalize()
{
	model_timer.reset_clock();
	my_node_id = "ALL";
}

Node* model::get_node(Node_Id id)
{
	if (nodes.find(id) == nodes.end())
	{
		throw NodeNotFoundException();
	}
	return model::nodes[id];
}

void model::create_node(Node_Type type, Node_Id id)
{
	model::nodes.emplace(std::pair<Node_Id, Node*>(id, new Node(type)));
}

Device* model::get_device(Device_Label label)
{
	return model::get_node(label.get_node_id())->get_device(label.get_device_id());
}

template <typename T>
void mangle_model(T* command, Device* device)
{
	state_interfaces::mangle_state(command, device);

}

void model::step()
{
	for (Command_List::iterator it = model::step_actions.begin(); it != model::step_actions.end(); ++it)
	{
		try 
		{
			mangle_model(it->command, model::get_device(it->label));
			it->command->time_to_complete -= model_timer.get_elapsed_time();

		}
		catch (std::exception&)
		{
			model::step_actions.erase(model::step_actions.begin(), model::step_actions.begin() + 1);
			std::rethrow_exception(std::current_exception());
		}
	}

	model_timer.update_time();
	model::step_actions.erase(model::step_actions.begin(), model::step_actions.end());
}



void model::stop_loop()
{
	model_running = false;
	model::clean_up();
}

void model::clean_up()
{
	model::nodes.clear();
}

