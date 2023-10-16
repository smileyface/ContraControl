#include "node_utilities.h"
#include "system_utilities.h"
#include "module_mains.h"

Node_Id node_utilities::local_node_handle = "Local Test Node";

void node_utilities::start_test_environment()
{
	create_node(node_utilities::local_node_handle);
	controller::add_command(Packed_Command(Commander::get_instance()->make_command<Node_Initalize>(NODE_TYPE::TEST, local_node_handle), 0));
	system_utilities::step(2);
}

void node_utilities::create_node(Node_Id id)
{
	controller::add_command(Packed_Command(Commander::get_instance()->make_command<Node_Create>(NODE_TYPE::TEST, id), 0));
	system_utilities::step(2);
}

void node_utilities::remove_node(Node_Id id)
{
	controller::add_command(Packed_Command(Commander::get_instance()->make_command<Node_Destroy>(id), 0));
	system_utilities::step(2);
}

void node_utilities::connect_node(Node_Id id1, Node_Id id2)
{ 
	controller::add_command(Packed_Command(Commander::get_instance()->make_command<Node_Connect>(id1, id2), 0));
	system_utilities::step(2);
}

Device_Label node_utilities::add_device(Node_Id id, Device_Creator creator)
{
	model::get_node(id)->register_device(creator);
	return(Device_Label(id, model::get_node(id)->get_device(creator.second)->get_id()));
}
