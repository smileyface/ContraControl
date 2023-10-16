/*****************************************************************//**
 * \file   node_connect.h
 * \brief  
 * 
 * \author kason
 * \date   October 2023
 *********************************************************************/

#ifndef NODE_CONNECT_COMMAND
#define NODE_CONNECT_COMMAND
#include "node_command.h"
#include "Interfaces/enums/node_type.h"

class Node_Connect : public Node_Command
{
public:
	Node_Connect() = delete;
	~Node_Connect();

	Node_Connect(Node_Id connected_name, Node_Id connecting_name);

	Node_Id get_connected_node();
	Node_Id get_connecting_node_name();

	virtual COMMAND_ENUM get_id()
	{
		return COMMAND_ENUM::NODE_CONNECT;
	}
private:
	Node_Id connected_node;
	Node_Id connecting_node_name;
};
#endif