#include "../commands/node/node_connect.h"

Node_Connect::~Node_Connect()
{ }

Node_Connect::Node_Connect(Node_Id connected_name, Node_Id connecting_name) :
	connecting_node_name(connecting_name)
{
	set_node_id(connected_name);
}

Node_Id Node_Connect::get_connected_node()
{
	return get_node_id();
}


Node_Id Node_Connect::get_connecting_node_name()
{
	return connecting_node_name;
}

