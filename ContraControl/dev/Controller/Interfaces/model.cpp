#include "model.h"
#include "../controller_main.h"
#include "../../Model/interfaces/controller.h"


void controller_interfaces::model_interface::send_command(Timed_Command timed_command)
{
	Model_Command m_command(timed_command.device_id, timed_command.command);
	model_interfaces::controller_interface::add_to_step(m_command);
}

void controller_interfaces::model_interface::request_command_add(Timed_Command timed_command)
{
	controller::controller_queue.push_back(timed_command);
	std::sort(controller::controller_queue.begin(), controller::controller_queue.end(), controller::sort_pair);
}

Device controller_interfaces::model_interface::get_device(Device_Name name)
{
	return model_interfaces::controller_interface::get_device(name);
}
