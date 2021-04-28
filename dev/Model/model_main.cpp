#include "model_main.h"

#include "../Interfaces/model_interface.h"
#include "../Interfaces/types/model_command.h"
#include "../Controller/Commands/common/initalize.h"
#include "../Utilities/Logging/logging.h"


Timer model_timer;

std::map<Node_Id, Node*> model::nodes;
bool model::model_running = true;

std::vector<Model_Command> model::step_actions;

Node_Id model::my_node;


void model::initalize()
{
	model_timer.reset_clock();
	my_node = "ALL";
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

/**
 * Run all commands lined up for this step. If an exception is thrown, the command is thrown away and the exception gets rethrown.
 * /todo Add details to the exception thrown
 */
void model::step()
{
	for (std::vector<Model_Command>::iterator it = model::step_actions.begin(); it != model::step_actions.end(); ++it)
	{
		try 
		{
			model::get_node(it->label.get_node_id())->run_command(it->label.get_device_id(), it->command);
		}
		catch (std::exception& exc)
		{
			model::step_actions.erase(model::step_actions.begin(), model::step_actions.begin() + 1);
			std::rethrow_exception(std::current_exception());
		}
	}

	model_timer.update_time();
	model::step_actions.erase(model::step_actions.begin(), model::step_actions.end());
}

void model::add_command(Device_Label label, Command* command)
{

}

void model::stop_loop()
{
	model_running = false;
}

void model::clean_up()
{
	model::nodes.clear();
}


void model::system_commands(Command* commands)
{
	if (commands->get_id() == COMMAND_ENUM::INITALIZE)
	{
		model::initalize();
	}
}
