#include "node/node_initalize.h"

Node_Initalize::~Node_Initalize()
{ }

Node_Initalize::Node_Initalize(Node_Id id) :
	node_id(id)
{ }

Node_Id Node_Initalize::get_node_id()
{
	return node_id;
}

