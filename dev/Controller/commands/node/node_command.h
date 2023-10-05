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

class Node_Command : public Command
{
public:
	Node_Command();
	virtual ~Node_Command();

	void set_node_id(Node_Id id);
	Node_Id get_node_id();

private:
	Node_Id id_to_command;
};

#endif