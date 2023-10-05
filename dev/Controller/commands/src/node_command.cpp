#include "../node/node_command.h"

Node_Command::Node_Command()
{ }

Node_Command::~Node_Command()
{ }

void Node_Command::set_node_id(Node_Id id)
{ 
	id_to_command = id;
}

Node_Id Node_Command::get_node_id()
{
	return id_to_command;
}
