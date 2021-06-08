/*****************************************************************//**
 * \file   device.h
 * \brief  
 * 
 * \author kason
 * \date   May 2021
 *********************************************************************/

#ifndef DEVICES_H
#define DEVICES_H

#include <map>

#include "Interfaces/types/device_label.h"

//#include "devices/device.h"
#include "devices/switch.h"
#include "devices/gradient.h"
#include "devices/channel.h"


/** 
 *  A list of types of devices.
 */
enum class DEVICE_IDENTIFIER : Device_Id
{
	DEVICE, ///<Generic Device
	SWITCH, ///<Device that is binary
	GRADIENT, ///<Device that has one channel that has various positions
    CHANNEL, ///<Device with multiple channels
	AUDIO ///<Device that controls audio
};

/**
 * A factory for making device instances.
 * \param creator A struct containing information to create the desired Device.
 * \return A pointer to the desired Device
 */
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

typedef std::map<Device_Id, Device*> Device_Id_Map;

#endif // !DEVICES_H