/*****************************************************************//**
 * \file   device.h
 * \brief  
 * 
 * \author kason
 * \date   May 2021
 *********************************************************************/

#ifndef DEVICES_H
#define DEVICES_H

#include <map>    //std::map

#include "Interfaces/types/device_label.h"

#include "devices/device.h"
//#include "devices/switch.h"
//#include "devices/gradient.h"
//#include "devices/channel.h"




/**
 * A factory for making device instances.
 * \param creator A struct containing information to create the desired Device.
 * \return A pointer to the desired Devic
 */

inline Device* create_device_instance(Device_Creator creator)
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
	default:
		the_device = new Device();
	}
	the_device->set_name(creator.second);
	return the_device;
}
/**
 Map of Id's that is indexed by unique Id's
 */
typedef std::map<Device_Id, Device*> Device_Id_Map;

#endif // !DEVICES_H