#include "../controller_interface.h"
#include "../model_interface.h"
#include "types/model_command.h"
#include "../Controller/controller_main.h"
#include "../Model/model_main.h"


void Controller_Interfaces::Model_Interface::send_command(Timed_Command timed_command)
{
	Model_Command m_command(timed_command.device_label, timed_command.command);
	Model_Interfaces::Controller_Interface::add_to_step(m_command);
}

void Controller_Interfaces::Model_Interface::request_command_add(Timed_Command timed_command)
{
	controller::add_command(timed_command);
}

void Controller_Interfaces::Main_Interface::start_controller()
{
	controller::initalize();
	controller::start_controller();
}
