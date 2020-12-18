#include "controller_interface.h"
#include "model_interface.h"
#include "../Controller/controller_main.h"


void Controller_Interfaces::Model_Interface::send_command(Timed_Command timed_command)
{
	Model_Command m_command(timed_command.device_label, timed_command.command);
	model_interfaces::controller_interface::add_to_step(m_command);
}

void Controller_Interfaces::Model_Interface::request_command_add(Timed_Command timed_command)
{
	controller::add_command(timed_command);
}

Device* controller_interfaces::model_interface::get_device_from_model(Node_Id node, Device_Name name)
{
	return model_interfaces::controller_interface::get_device(node, name);
}
