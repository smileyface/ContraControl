#include "device_utilities.h"
#include "system_testings.h"
#include "module_mains.h"

int device_utilities::device_in_use = 0;
Device* device_utilities::get_nominal_state(DEVICE_IDENTIFIER device, Command* command)
{
	Device* ds = create_device_instance(Device_Creator((Device_Id)device, "Nominal"));
	switch (command->get_id())
	{
	case COMMAND_ENUM::TRANSITION:
		ds = get_nominal_tranistion_state(static_cast<Transition*>(command));
	case COMMAND_ENUM::ON:
		ds->power = true;
	case COMMAND_ENUM::OFF:
	case COMMAND_ENUM::INITALIZE:
		ds->initalized = true;
		ds->valid = true;
	case COMMAND_ENUM::INVALID:
		break;
	}
	return ds;
}

Channel_Device* device_utilities::get_nominal_tranistion_state(Transition* command)
{
	Channel_Device* ds = new Channel_Device();
	ds->transitioning = !command->completed();
	return ds;
}

void device_utilities::setup_node(Node_Id id, Node_Type type)
{
	model::initalize_my_node(id, type);
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

Device* device_utilities::command_device(Device_Label label, Command* command)
{
	controller::add_command(Timed_Command(command, label, 0));
	system_util::step(1);
	return get_nominal_state(model::get_device(label)->get_device_type(), command);
}

Device* device_utilities::finish_command(Device_Label label, Command* command)
{
	while (!command->completed())
	{
		system_util::step(1);
	}
	system_util::step(1);
	return get_nominal_state(model::get_device(label)->get_device_type(), command);
}

void device_utilities::initalize_device(Device_Label label)
{
	command_device(label, new Initalize());
}