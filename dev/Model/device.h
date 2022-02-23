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

//#include "Interfaces/types/device_label.h"

#include "devices/device.h"
//#include "devices/switch.h"
//#include "devices/gradient.h"
//#include "devices/channel.h"




/**
 * A factory for making device instances.
 * \param creator A struct containing information to create the desired Device.
 * \return A pointer to the desired Devic
 */

Device* create_device_instance(Device_Creator creator);
/**
 Map of Id's that is indexed by unique Id's
 */
typedef std::map<Device_Id, Device*> Device_Id_Map;

#endif // !DEVICES_H