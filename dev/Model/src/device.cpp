#include <typeinfo> //typeid

#include "../devices/device.h"
#include "Utilities/exceptions.h"


Device* create_device_instance(Device_Creator creator)
{
	Device* the_device;
	switch ((DEVICE_IDENTIFIER)creator.first)
	{
	case DEVICE_IDENTIFIER::SWITCH:
		the_device = new Device(DEVICE_IDENTIFIER::SWITCH, 0);
		break;
	case DEVICE_IDENTIFIER::GRADIENT:
		the_device = new Device(DEVICE_IDENTIFIER::GRADIENT, 1);
		break;
	case DEVICE_IDENTIFIER::RGB:
		the_device = new Device(DEVICE_IDENTIFIER::RGB, 3);
		break;
	case DEVICE_IDENTIFIER::INVALID:
	default:
		the_device = new Device();
	}
	the_device->set_name(creator.second);
	return the_device;
}

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

bool Device::is_initalized()
{
	return initalized;
}

bool Device::is_valid()
{
	return valid;
}

void Device::turn_on()
{
	if (is_initalized() == false)
	{
		valid = false;
		return;
	}
	power = true;
}

void Device::turn_off()
{
	if (is_initalized() == false)
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

Channel Device::get_channel(int channel)
{
	return channels[channel];
}

bool Device::operator==(const Device& ld)
{
	bool type_check = typeid(*this).name() == typeid(ld).name();
	bool device_name = this->device_name == ld.device_name;
	return type_check && device_name;
}