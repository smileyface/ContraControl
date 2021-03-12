#ifndef DEVICES_H
#define DEVICES_H

#include <string>

#include "devices/device.h"
#include "devices/switch.h"
#include "devices/gradient.h"
#include "devices/channel.h"

enum class DEVICE_IDENTIFIER : uint16_t
{
	DEVICE,
	SWITCH,
	GRADIENT,
    CHANNEL,
	AUDIO
};

inline Device* create_device_instance(Device_Creator creator)
{
	Device* the_device;
	switch ((DEVICE_IDENTIFIER)creator.first)
	{
	case DEVICE_IDENTIFIER::SWITCH:
		the_device = new Switch_Device();
		break;
	default:
		the_device = new Device();
	}
	the_device->set_name(creator.second);
	return the_device;
}

#endif // !DEVICES_H