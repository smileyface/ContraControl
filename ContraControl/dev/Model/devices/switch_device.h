#ifndef SWITCH_DEVICE_H
#define SWITCH_DEVICE_H

#include "device.h"

class SwitchDevice: public Device
{
public:
	SwitchDevice();
	void run_command(Command command);
	~SwitchDevice();


};

#endif // !SWITCH_DEVICE_H