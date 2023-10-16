#include "../commands/node/node_connect.h"

Node_Connect::~Node_Connect()
{ }

Node_Connect::Node_Connect(Node_Id connected_name, Node_Id connecting_name) :
	connected_node(connected_name),
	connecting_node_name(connecting_name)
{ }

Node_Id Node_Connect::get_connected_node()
{
	return connected_node;
}


Node_Id Node_Connect::get_connecting_node_name()
{
	return connecting_node_name;
}

