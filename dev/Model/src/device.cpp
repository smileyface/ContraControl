#include <typeinfo> //typeid

#include "../devices/device.h"

Device::Device()
{

}

Device::Device(DEVICE_IDENTIFIER type_of_device, int number_of_channels)
{
	type = type_of_device;
	for (int i = 0; i < number_of_channels; i++)
	{
		channels.push_back(UNUSED);
	}
}

Device::~Device()
{

}

Device_Id Device::get_id()
{
	return id;
}

Device_Name Device::get_name()
{
	return device_name;
}

Device_Name Device::get_full_name()
{
	Device_Name device_name = typeid(*this).name();
	return device_name.erase(0, 6) + "::" + get_name();
}

DEVICE_IDENTIFIER Device::get_device_type() 
{ 
	return type; 
}

void Device::set_name(Device_Name new_name)
{
	device_name = new_name;
}

void Device::set_id(Device_Id new_id)
{
	id = new_id;
}

bool Device::validity_check()
{
	return true;
}

void Device::initalize(Device_Name name)
{
	device_name = name;
	initalized = true;
	valid = validity_check();
}

bool Device::get_power()
{
	return power;
}

void Device::turn_on()
{
	if (initalized == false)
	{
		valid = false;
		return;
	}
	power = true;
}

void Device::turn_off()
{
	if (initalized == false)
	{
		valid = false;
		return;
	}
	power = false;
}

void Device::set_channel(int channel, Channel value)
{
	channels[channel] = value;
}

bool Device::operator==(const Device& ld)
{
	bool type_check = typeid(*this).name() == typeid(ld).name();
	bool device_name = this->device_name == ld.device_name;
	return type_check && device_name;
}