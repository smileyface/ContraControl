#ifndef DEVICES_H
#define DEVICES_H

#include <string>

#include "devices/device.h"
#include "devices/switch.h"
#include "devices/gradient.h"
#include "devices/channel.h"

typedef uint16_t Device_Id;
typedef std::string Device_Name;
typedef std::pair<uint16_t, Device_Name> Device_Creator;

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
	case DEVICE_IDENTIFIER::GRADIENT:
		the_device = new Gradient_Device();
		break;
	default:
		the_device = new Device();
	}
	the_device->set_name(creator.second);
	return the_device;
}

#endif // !DEVICES_H