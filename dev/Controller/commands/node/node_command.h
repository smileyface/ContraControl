/*****************************************************************//**
 * \file   node_command.h
 * \brief  
 * 
 * 
 * \author kason
 * \date   October 2023
 *********************************************************************/
#ifndef NODE_COMMAND_BASE
#define NODE_COMMAND_BASE
#include "../command.h"
#include "Interfaces/types/device_label.h"

/**
 * Send a general command to a node 
 */
class Node_Command : public Command
{
public:
	Node_Command();
	virtual ~Node_Command();
	/**
	 * Set a node to command.
	 * 
	 * \param id Id of the node.
	 */
	void set_node_id(Node_Id id);
	/**
	 * \return Id of the node to command.
	 */
	Node_Id get_node_id();

private:
	Node_Id id_to_command;
};

#endif