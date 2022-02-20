#include "node_utilities.h"
#include "system_testings.h"
#include "module_mains.h"

void node_utilities::create_node(Node_Id id)
{
	model::create_node(Node_Type::TEST, id);
}