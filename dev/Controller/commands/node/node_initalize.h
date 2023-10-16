/*****************************************************************//**
 * \file   node_initalize.h
 * \brief  
 * 
 * \author kason
 * \date   October 2023
 *********************************************************************/

#ifndef INITALIZE_NODE_COMMAND
#define INITALIZE_NODE_COMMAND

#include "node_command.h"
#include "Interfaces/enums/node_type.h"

class Node_Initalize : public Node_Command
{
public:
	Node_Initalize() = delete;
	~Node_Initalize();

	Node_Initalize(Node_Id id);

	Node_Id get_node_id();

	virtual COMMAND_ENUM get_id()
	{
		return COMMAND_ENUM::NODE_INITALIZE;
	}
private:
	Node_Id node_id;
};


#endif
