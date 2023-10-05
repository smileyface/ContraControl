#include "../node/node_create.h"

Node_Create::Node_Create(NODE_TYPE type, Node_Id id) :
	type(type)
{ 
	set_node_id(id);
}

Node_Create::~Node_Create()
{

}

Node_Create::get_type()
{
	return type;
}
