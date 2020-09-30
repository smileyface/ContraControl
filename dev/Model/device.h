#ifndef DEVICES_H
#define DEVICES_H

#include <string>



#include "devices/basic/device.h"
#include "devices/basic/switch.h"
#include "devices/basic/gradient.h"

enum class DEVICE_IDENTIFIER
{
	DEVICE,
	SWITCH,
	GRADIENT
};

#endif // !DEVICES_H