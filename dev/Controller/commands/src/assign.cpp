#include "../device/assign.h"

Assign::Assign()
{
	channel = 0;
	value = 0;
}

Assign::Assign(int channel_number, Channel new_value)
{
	value = new_value;
	channel = channel_number;
}

Assign::Assign(Channel new_value)
{
	channel = 0;
	value = new_value;
}