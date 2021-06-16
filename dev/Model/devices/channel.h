#ifndef CHANNEL_DEVICE_H
#define CHANNEL_DEVICE_H
#include "device.h"

typedef unsigned char Channel;

class Channel_Device : public Device
{
public:
	Channel_Device() {
	}
	Channel_Device(Device* dev) {
		initalized = dev->initalized;
		power = dev->power;
		valid = dev->valid;
		transitioning = false;
	}
	virtual DEVICE_IDENTIFIER get_device_type() { return DEVICE_IDENTIFIER::CHANNEL; }
	bool transitioning;
	std::vector<Channel> channels;
protected:
};

#endif