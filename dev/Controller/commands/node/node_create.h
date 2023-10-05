/*****************************************************************//**
 * \file   node_create.h
 * \brief  
 * 
 * \author kason
 * \date   October 2023
 *********************************************************************/

#include "node_command.h"
#include "Interfaces/enums/node_type.h"

class Node_Create : public Node_Command
{
public:
	Node_Create() = delete;
	virtual ~Node_Create();

	Node_Create(NODE_TYPE type, Node_Id id);

	NODE_TYPE get_type();

	virtual COMMAND_ENUM get_id()
	{
		return COMMAND_ENUM::NODE_CREATION;
	}

private:
	NODE_TYPE type;
};
