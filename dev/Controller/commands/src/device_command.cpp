#include "../device/device_command.h"

void Device_Command::set_label(Device_Label label)
{
	this->label = label;
}

Device_Label Device_Command::get_label()
{
	return this->label;
}
