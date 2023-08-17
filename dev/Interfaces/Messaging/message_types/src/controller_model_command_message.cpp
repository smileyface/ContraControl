#include "../command_messages/controller_model_command_message.h"

Controller_Model_Command::Controller_Model_Command()
{ }

Packed_Command Controller_Model_Command::get_command()
{
	return command;
}

Controller_Model_Command::Controller_Model_Command(Packed_Command tc)
{
	command = tc;

}
