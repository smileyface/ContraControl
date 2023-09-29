#include "../device/assign.h"


Assign::Assign(Device_Label label, Channel new_value) :
	value(new_value),
	channel(0)
{
	set_label(label);
}

Assign::Assign(Device_Label label, int channel_number, Channel new_value) :
	value(new_value),
	channel(channel_number)
{ 
	set_label(label);
}
