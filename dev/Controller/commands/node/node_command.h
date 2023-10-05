/*****************************************************************//**
 * \file   node_command.h
 * \brief  
 * 
 * 
 * \author kason
 * \date   October 2023
 *********************************************************************/

#include "command.h"
#include "Interfaces/types/device_label.h"

class Node_Command : public Command
{
public:
	Node_Command() = delete;
	virtual ~Node_Command();

	void set_node_id(Node_Id id);
	Node_Id get_node_id();

private:
	Node_Id id_to_command;
};
