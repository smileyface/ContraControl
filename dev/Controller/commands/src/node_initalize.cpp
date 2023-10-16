#include "node/node_initalize.h"

Node_Initalize::~Node_Initalize()
{ }

Node_Initalize::Node_Initalize(NODE_TYPE type, Node_Id id) :
	node_type(type),
	node_id(id)
{ }

Node_Id Node_Initalize::get_node_id()
{
	return node_id;
}

NODE_TYPE Node_Initalize::get_node_type()
{
	return node_type;
}
