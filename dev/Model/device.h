#ifndef DEVICES_H
#define DEVICES_H

#include <string>

typedef uint16_t Device_Id;
typedef std::string Device_Name;

#define INVALID_DEVICE UINT16_MAX

#include "devices/basic/device.h"
#include "devices/basic/switch.h"
#include "devices/basic/gradient.h"

#endif // !DEVICES_H