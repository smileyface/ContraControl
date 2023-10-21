/*****************************************************************//**
 * \file   node_create.h
 * \brief  
 * 
 * \author kason
 * \date   October 2023
 *********************************************************************/

#include "node_command.h"
#include "Interfaces/enums/node_type.h"

/**
 * Create a node on the model.
 */
class Node_Create : public Node_Command
{
public:
	Node_Create() = delete;
	virtual ~Node_Create();

	/**
	 * \param type Type of the node. Mainly what kind of devices will be connected. 
	 * \param id Common name of the new node.
	 */
	Node_Create(NODE_TYPE type, Node_Id id);

	/**
	 * \return Type of the new node.
	 */
	NODE_TYPE get_type();

	virtual COMMAND_ENUM get_id()
	{
		return COMMAND_ENUM::NODE_CREATION;
	}

private:
	NODE_TYPE type;
};
