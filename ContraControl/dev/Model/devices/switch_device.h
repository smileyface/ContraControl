#ifndef SWITCH_DEVICE_H
#define SWITCH_DEVICE_H

#include "../device.h"

class SWITCH_DEVICE_COMMANDS : public DEVICE_COMMAND
{
public:
	Command_Def ON = 1;
	Command_Def OFF = 2;
};

class SwitchDevice: public Device
{
public:
	SwitchDevice();
	~SwitchDevice();

	void initalize();

};

#endif // !SWITCH_DEVICE_H