/*****************************************************************//**
 * \file   node_destroy.h
 * \brief  
 * 
 * \author kason
 * \date   October 2023
 *********************************************************************/

#ifndef NODE_DESTROY_COMMAND
#define NODE_DESTROY_COMMAND
#include "node_command.h"

/**
 * Destroy a node on the model.
 */
class Node_Destroy : public Node_Command
{
public:
	Node_Destroy() = delete;
	virtual ~Node_Destroy();

	/**
	 * \param id Name of the node to destroy.
	 */
	Node_Destroy(Node_Id id);

	virtual COMMAND_ENUM get_id()
	{
		return COMMAND_ENUM::NODE_DESTORY;
	}
};

#endif