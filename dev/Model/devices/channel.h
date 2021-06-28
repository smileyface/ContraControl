/*****************************************************************//**
 * \file   channel.h
 * \brief  
 * 
 * \author kason
 * \date   June 2021
 *********************************************************************/

#ifndef CHANNEL_DEVICE_H
#define CHANNEL_DEVICE_H
#include "device.h"


#include "Interfaces/types/channel.h"

/**
 A Device that has added states of a string of channels for various purposes and whether those channels are expecting a value change.
 */
class Channel_Device : public Device
{
public:
	Channel_Device() {
	}
	/**
	 Cast constructor for parent Device.
	 \param dev Device for transformation.
	 */
	Channel_Device(Device* dev) {
		initalized = dev->initalized;
		power = dev->power;
		valid = dev->valid;
		transitioning = false;
	}
	/**
	\return Type of device based off of the DEVICE_IDENTIFIER enum table.
	*/
	virtual DEVICE_IDENTIFIER get_device_type() { return DEVICE_IDENTIFIER::CHANNEL; }
	/**
	 State describing whether the channels of the device are moving.
	 */
	bool transitioning = false;
	/**
	 Position of each channel. 1-255 range. 0 is reserved for unused channels
	 */
	std::vector<Channel> channels;
protected:
};

#endif