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

/**
 * Initalize a node as local
 */
class Node_Initalize : public Node_Command
{
public:
	Node_Initalize() = delete;
	~Node_Initalize();

	/**
	 * \param id Name of node to make local.
	 */
	Node_Initalize(Node_Id id);

	virtual COMMAND_ENUM get_id()
	{
		return COMMAND_ENUM::NODE_INITALIZE;
	}
private:
};


#endif
