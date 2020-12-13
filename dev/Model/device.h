#ifndef DEVICES_H
#define DEVICES_H

#include <string>



#include "devices/device.h"
#include "devices/switch.h"
#include "devices/gradient.h"
#include "devices/channel.h"

enum class DEVICE_IDENTIFIER
{
	DEVICE,
	SWITCH,
	GRADIENT,
    CHANNEL,
	AUDIO
};

#endif // !DEVICES_H