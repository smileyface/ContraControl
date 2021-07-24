#include "model_main.h"

#include "Logging/logging.h"
#include "Interfaces/types/state.h"


Timer model_timer;

bool model::model_running = true;

Command_List model::step_actions;

Node model::my_node;


void model::initalize()
{
	model_timer.reset_clock();
}

Node* model::get_node(Node_Id id)
{
	if (my_node.get_id() == id)
	{
		return &my_node;
	}
	return my_node.get_connection(id);
}

void model::create_node(Node_Type type, Node_Id id)
{
	my_node.add_connection(type, id);
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
	my_node.clear_node();
}

void model::initalize_my_node(Node_Id id, Node_Type type)
{
	my_node.initalize_local_control(id, type);
}

