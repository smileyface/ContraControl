#include "model_main.h"

#include "types.h"
#include "../Interfaces/model_interface.h"
#include "../Controller/Commands/common/initalize.h"
#include "../Utilities/Logging/logging.h"


Timer model_timer;

std::map<Node_Id, Node> model::nodes;
bool model::model_running = true;

std::vector<Model_Command> model::step_actions;
std::map<Device_Id, Device_Name> model::id_map;


void model::initalize()
{

}

Node get_node(Node_Id id)
{
	return model::nodes[id];
}


void model::step()
{
	std::vector<int> completed_index = model::run_commands();

	for (size_t i = 0; i < completed_index.size(); i++) {
		model::step_actions.erase(step_actions.begin() + completed_index[i]);
	}
	model_timer.update_time();
}

void model::stop_loop()
{
	model_running = false;
}

void model::clean_up()
{
	model::nodes.clear();
}

std::vector<int> model::run_commands()
{
	std::vector<int> completed_index;
	//for (int i = 0; i < model::step_actions.size(); i++) {

	//		model::get_device(model::step_actions[i].id)->run_command(model::step_actions[i].command);
	//		model::system_commands(model::step_actions[i].command);
	//		if(model::step_actions[i].command->completed())
	//			completed_index.push_back(i);

	//}
	return completed_index;
}

void model::system_commands(Command* commands)
{
	if (commands->get_id() == COMMAND_ENUM::INITALIZE)
	{
		model::id_map.clear();
		model::initalize();
	}
}
