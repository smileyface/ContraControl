/*****************************************************************//**
 * \file   controller_model_command_message.h
 * \brief  
 * 
 * \author kason
 * \date   August 2023
 *********************************************************************/

#include "../internal_message_type.h"
#include "Interfaces/types/packed_command.h"

/**
 * Controller commands to the Model
 */
class Controller_Model_Command : public Internal_Message
{
public:
	Controller_Model_Command();
	/**
	 * @brief Constructor for a Command Internal_Message.
	 * 
	 * This creates non-null Command Internal_Message.
	 * 
	 * @param cmd A packed command to send over the Message_Relay. 
	 */
	Controller_Model_Command(const Packed_Command& cmd);

	/**
	 * @brief Returns a pointer to the Command.
	 * @returns Command pointer.
	 */
	Packed_Command get_command();

private:
	Packed_Command command;

};
