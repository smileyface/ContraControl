#include "controller.h"
#include "../model_main.h"
#include "../../Controller/Interfaces/model.h"
#include "../../Controller/types.h"
#include "../../Controller/Commands/basic/initalize.h"

void model_interfaces::controller_interface::add_to_step(Model_Command theCommand)
{
	model::step_actions.emplace_back(theCommand);
}

void model_interfaces::controller_interface::request_command(Model_Command theCommand, double seconds_to_execute)
{
	Timed_Command command(theCommand.command, theCommand.id, seconds_to_execute);
	controller_interfaces::model_interface::request_command_add(command);
}

Command* model_interfaces::controller_interface::get_command_object(COMMAND_ID Command, std::string args)
{
	switch (Command) {
	case COMMAND_ID::INITALIZE:
		return new Initalize(args);
	}
	return nullptr;
}

Device model_interfaces::controller_interface::get_device(Device_Name name)
{
	return *model::known_devices[name];
}
