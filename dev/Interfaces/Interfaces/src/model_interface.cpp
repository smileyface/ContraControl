

#include "../model_interface.h"
#include "../controller_interface.h"

#include "../Model/model_main.h"
#include "../Controller/controller_main.h"
#include "../Controller/commands.h"
#include "Interfaces/types/device_label.h"



void Model_Interfaces::Controller_Interface::add_to_step(Model_Command theCommand)
{
	model::command_model(theCommand);
}

void Model_Interfaces::Controller_Interface::request_command(Model_Command theCommand, double seconds_to_execute)
{
	Timed_Command command(theCommand.command, theCommand.label, seconds_to_execute);
	Controller_Interfaces::Model_Interface::request_command_add(command);
}

void Model_Interfaces::Main_Interface::start_model()
{
	model::initalize();
	model::start_loop();
}

void Model_Interfaces::Main_Interface::stop_model()
{
	model::stop_loop();
	model::clean_up();
}
