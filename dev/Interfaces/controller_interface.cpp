#include "controller_interface.h"
#include "model_interface.h"
#include "../Controller/controller_main.h"


void controller_interfaces::model_interface::send_command(Timed_Command timed_command)
{
	Model_Command m_command(timed_command.device_id, timed_command.command);
	model_interfaces::controller_interface::add_to_step(m_command);
}

void controller_interfaces::model_interface::request_command_add(Timed_Command timed_command)
{
	controller::add_command(timed_command);
}

Device controller_interfaces::model_interface::get_device_from_model(Device_Name name)
{
	return model_interfaces::controller_interface::get_device(name);
}

Device controller_interfaces::model_interface::get_device(Device_Name name)
{
	return model_interfaces::controller_interface::get_device(name);
}
