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
	//for (std::map<Node_Id, Node*>::iterator node_iterator = model::nodes.begin(); node_iterator != model::nodes.end(); ++node_iterator)
	//{
	//	std::vector<Device_Id> node_devices = node_iterator->second->get_devices();
	//	for (std::vector<Device_Id>::iterator device_iterator = node_devices.begin(); device_iterator != node_devices.end(); ++device_iterator)
	//		model_interfaces::controller_interface::request_command(Model_Command(Device_Label(node_iterator->first, *device_iterator), new Initalize()), 0);
	//}
		
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
	for (std::vector<Model_Command>::iterator it = model::step_actions.begin(); it != model::step_actions.end(); ++it)
	{
		model::get_device(it->label)->run_command(it->command);
	}
	model::step_actions.clear();
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
