#include "../device/device_destruction.h"

Device_Destruction::~Device_Destruction()
{ }

Device_Destruction::Device_Destruction(Device_Label label) :
	device(label)
{
}

Device_Label Device_Destruction::get_device()
{
	return device;
}
