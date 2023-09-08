#include "../device/on.h"

On::On(Device_Label label)
{
	set_label(label);
}

On::~On()
{
	Device_Command::~Device_Command();
}
