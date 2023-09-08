#include "../device/off.h"

Off::Off(Device_Label label)
{
	set_label(label);
}

Off::~Off()
{
	Device_Command::~Device_Command();
}
