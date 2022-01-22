#include "model_main.h"

#include <algorithm>

#include "Logging/logging.h"
#include "Interfaces/types/state.h"


Timer model_timer;
bool model::model_running = true;
Command_List model::step_actions;

System_Alerts* model::model_alert_interface;
Node model::my_node;


void model::initalize()
{
	model_timer.reset_clock();
	model_alert_interface = System_Alerts::get_instance();
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

void model_loop()
{
	while (model::model_running)
	{
		model::step();
	}
}

void model::start_loop()
{
	model_running = true;
	model_alert_interface->push(Alert(ALERT_PRIORITY::INFO, "Model Started", subsystem_name));

	//TODO: Thread model loop
}

void model::stop_loop()
{
	model_running = false;
	model::clean_up();
}



void model::clean_up()
{
	my_node.clear_node();
	network::teardown_network_interfaces();
}

void model::initalize_my_node(Node_Id id, Node_Type type)
{
	my_node.initalize_local_control(id, type);
}

/**
 *  \cond
 */
struct compare
{
	Model_Command key;
	compare(Model_Command const& i) : key(i) {}
	bool operator()(Model_Command const& i)
	{
		bool same_command = key.command == i.command;
		bool same_device = key.label == i.label;
		return same_command && same_device;
	}
};
/**
 * \endcond
 */

void model::command_model(Model_Command command)
{
	auto found = std::find_if(model::step_actions.begin(), model::step_actions.end(), compare(command));
	if (found == model::step_actions.end() || model::step_actions.size() == 0)
	{
		model::step_actions.emplace_back(command);
	}
}