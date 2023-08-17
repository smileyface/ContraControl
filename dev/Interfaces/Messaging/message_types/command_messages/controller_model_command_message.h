/*****************************************************************//**
 * \file   controller_model_command_message.h
 * \brief  
 * 
 * \author kason
 * \date   August 2023
 *********************************************************************/

#include "../internal_message_type.h"
#include "Interfaces/types/packed_command.h"

class Controller_Model_Command : public Internal_Message
{
public:
	Controller_Model_Command();
	Controller_Model_Command(Packed_Command tc);

	Packed_Command get_command();

private:
	Packed_Command command;
};
