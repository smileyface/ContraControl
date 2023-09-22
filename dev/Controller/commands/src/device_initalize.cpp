#include "../device/device_initalize.h"

Initalize_Device::~Initalize_Device()
{ }

Initalize_Device::Initalize_Device(Device_Label label, std::string device_common_name)
{ 
	this->name = device_common_name;
	this->label = label;
}
