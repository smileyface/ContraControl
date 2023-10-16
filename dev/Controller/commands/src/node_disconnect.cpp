#include "../node/node_disconnect.h"

Node_Disconnect::~Node_Disconnect()
{ }

Node_Disconnect::Node_Disconnect(Node_Id disconnected_node_name, Node_Id disconnecting_node_name) :
	disconnected_node(disconnected_node_name),
	disconnecting_node(disconnecting_node_name)
{ }

Node_Id Node_Disconnect::get_disconnected_node()
{
	return disconnected_node;
}

Node_Id Node_Disconnect::get_disconnecting_node()
{
	return disconnecting_node;
}

