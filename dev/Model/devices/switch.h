#ifndef SWITCH_DEVICE_H
#define SWITCH_DEVICE_H

#include "device.h"

class Switch_Device: public Device
{
public:
	Switch_Device() { };
	~Switch_Device() {};

	bool get_power()
	{
		return state.power;
	}

private:

};

#endif // !SWITCH_DEVICE_H