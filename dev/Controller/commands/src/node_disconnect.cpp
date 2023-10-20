#include "../node/node_disconnect.h"

Node_Disconnect::~Node_Disconnect()
{ }

Node_Disconnect::Node_Disconnect(Node_Id disconnected_node_name, Node_Id disconnecting_node_name) :
	disconnecting_node(disconnecting_node_name)
{
	set_node_id(disconnected_node_name);
}

Node_Id Node_Disconnect::get_disconnected_node()
{
	return get_node_id();
}

Node_Id Node_Disconnect::get_disconnecting_node()
{
	return disconnecting_node;
}

