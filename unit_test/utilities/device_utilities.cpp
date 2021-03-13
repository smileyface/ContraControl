#include "device_utilities.h"
#include "system_testings.h"
#include "module_mains.h"

int device_utilities::device_in_use = 0;
Device_State device_utilities::get_nominal_state(Command* command)
{
		Device_State ds;
		switch (command->get_id())
		{
		case COMMAND_ENUM::TRANSITION:
			ds.transitioning = true;
		case COMMAND_ENUM::ON:
			ds.power = true;
		case COMMAND_ENUM::OFF:
		case COMMAND_ENUM::INITALIZE:
			ds.initalized = true;
			ds.valid = true;
			break;
		}
		return ds;
}

void device_utilities::create_node(Node_Id id)
{
	model::create_node(Node_Type::TEST, id);
}

Device_Label device_utilities::add_device(Node_Id id, Device_Creator creator)
{
	model::get_node(id)->register_device(creator);
	return(Device_Label(id, model::get_node(id)->get_device(creator.second)->get_id()));
}

Device_State device_utilities::command_device(Device_Label label, Command* command)
{
	controller::add_command(Timed_Command(command, label, 0));
	system_util::step(1);
	return get_nominal_state(command);
}

Device_State device_utilities::finish_command(Command* command)
{
	while (!command->completed())
	{
		system_util::step(1);
	}
	return get_nominal_state(command);
}

void device_utilities::initalize_device(Device_Label label)
{
	command_device(label, new Initalize());
}