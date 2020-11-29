#include <algorithm>

#include "model_interface.h"
#include "controller_interface.h"

#include "../Model/model_main.h"
#include "../Controller/controller_main.h"
#include "../Controller/types.h"
#include "../Controller/commands.h"

struct compare
{
	Model_Command key;
	compare(Model_Command const& i) : key(i) {}
	bool operator()(Model_Command const& i)
	{
		return get_command_name(key.command) == get_command_name(i.command);
	}
};

void model_interfaces::controller_interface::add_to_step(Model_Command theCommand)
{
	auto found = std::find_if(model::step_actions.begin(), model::step_actions.end(), compare(theCommand));
	if (found == model::step_actions.end() || model::step_actions.size() == 0)
	{
		model::step_actions.emplace_back(theCommand);
	}
	
}

void model_interfaces::controller_interface::request_command(Model_Command theCommand, double seconds_to_execute)
{
	Timed_Command command(theCommand.command, theCommand.id, seconds_to_execute);
	controller_interfaces::model_interface::request_command_add(command);
}


Device model_interfaces::controller_interface::get_device(Device_Name name)
{
	return *model::known_devices[name];
}
