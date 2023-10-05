#include "node_utilities.h"
#include "system_utilities.h"
#include "module_mains.h"

Node_Id node_utilities::local_node_handle = "Local Test Node";

void node_utilities::start_test_environment()
{
	model::initalize_my_node(node_utilities::local_node_handle);
}

void node_utilities::create_node(Node_Id id)
{
	controller::add_command(Packed_Command(Commander::get_instance()->make_command<Node_Create>(NODE_TYPE::TEST, id), 0));
	system_utilities::step(2);
}

Device_Label node_utilities::add_device(Node_Id id, Device_Creator creator)
{
	model::get_node(id)->register_device(creator);
	return(Device_Label(id, model::get_node(id)->get_device(creator.second)->get_id()));
}
