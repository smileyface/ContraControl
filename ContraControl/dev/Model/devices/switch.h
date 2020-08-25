#ifndef SWITCH_DEVICE_H
#define SWITCH_DEVICE_H

#include "device.h"

class SwitchDevice: public Device
{
public:
	SwitchDevice() { position = false; };
	~SwitchDevice() {};

	void set_position(bool new_position)
	{
		position = new_position;
	}

	bool get_position()
	{
		return position;
	}

	virtual std::string type_id() { return "Switch"; };

private:
	bool position;

};

#endif // !SWITCH_DEVICE_H