/*****************************************************************//**
 * \file   node_disconnect.h
 * \brief  
 * 
 * \author kason
 * \date   October 2023
 *********************************************************************/
#ifndef NODE_DISCONNECT_COMMAND
#define NODE_DISCONNECT_COMMAND
#include "node_command.h"

/**
 * Remove a connection between two nodes.
 */
class Node_Disconnect : public Node_Command
{
public:
	Node_Disconnect() = delete;
	~Node_Disconnect();
	/** 
	*Constructor.
	*
	* \param disconnected_node_name The ID of the node to disconnect.
	* \param disconnecting_node_name The ID of the node to disconnect.
	*/
	Node_Disconnect(Node_Id disconnected_node_name, Node_Id disconnecting_node_name);

	/**
	* \return ID of node to disconnect
	*/
	Node_Id get_disconnected_node();
	/**
	* \return ID of node to disconnect
	*/
	Node_Id get_disconnecting_node();

	virtual COMMAND_ENUM get_id()
	{
		return COMMAND_ENUM::NODE_DISCONNECT;
	}

private:
	Node_Id disconnecting_node;
};


#endif // !NODE_DISCONNECT_COMMAND
