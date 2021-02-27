#include "model_main.h"

#include "types.h"
#include "../Interfaces/model_interface.h"
#include "../Controller/Commands/common/initalize.h"
#include "../Utilities/Logging/logging.h"


Timer model_timer;

std::map<Node_Id, Node*> model::nodes;
bool model::model_running = true;

std::vector<Model_Command> model::step_actions;
std::map<Device_Id, Device_Name> model::id_map;


void model::initalize()
{

}

Node* model::get_node(Node_Id id)
{
	return model::nodes[id];
}

void model::create_node(Node_Type type, Node_Id id)
{
	model::nodes.emplace(std::pair<Node_Id, Node*>(id, new Node(type)));
}

Device* model::get_device(Device_Label label)
{
	return model::get_node(label.first)->get_device(label.second);
}

void model::step()
{

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
		model::id_map.clear();
		model::initalize();
	}
}
