#include <algorithm>

#include "model_interface.h"
#include "controller_interface.h"

#include "../Model/model_main.h"
#include "../Controller/controller_main.h"
#include "../Controller/commands.h"
#include "Interfaces/types/device_label.h"

/** 
 *  \cond
 */
struct compare
{
	Model_Command key;
	compare(Model_Command const& i) : key(i) {}
	bool operator()(Model_Command const& i)
	{
		bool same_command = key.command == i.command; 
		bool same_device = key.label == i.label;
		return same_command&&same_device;
	}
};
/**
 * \endcond
 */

void Model_Interfaces::Controller_Interface::add_to_step(Model_Command theCommand)
{
	auto found = std::find_if(model::step_actions.begin(), model::step_actions.end(), compare(theCommand));
	if (found == model::step_actions.end() || model::step_actions.size() == 0)
	{
		model::step_actions.emplace_back(theCommand);
	}
	
}

void Model_Interfaces::Controller_Interface::request_command(Model_Command theCommand, double seconds_to_execute)
{
	Timed_Command command(theCommand.command, theCommand.label, seconds_to_execute);
	Controller_Interfaces::Model_Interface::request_command_add(command);
}
