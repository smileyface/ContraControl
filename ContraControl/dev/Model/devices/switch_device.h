#ifndef SWITCH_DEVICE_H
#define SWITCH_DEVICE_H

#include "device.h"

class SwitchDevice: public Device
{
public:
	SwitchDevice(std::string name);
	~SwitchDevice();
	void run_command(Command* command);
};

#endif // !SWITCH_DEVICE_H