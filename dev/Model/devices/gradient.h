/*****************************************************************//**
 * \file   gradient.h
 * \brief  
 * 
 * \author kason
 * \date   May 2021
 *********************************************************************/
#ifndef GRADIENT_DEVICE_H
#define GRADIENT_DEVICE_H

#include "channel.h"

/** 
 *  A non-binary device.
 */
class Gradient_Device: public Channel_Device
{
public:
	Gradient_Device() 
	{
		channels.push_back(0);
		transitioning = false;
	};
	~Gradient_Device() {};
	virtual DEVICE_IDENTIFIER get_device_type() { return DEVICE_IDENTIFIER::GRADIENT; }
	/**
	 * Return position in the gradient.
	 * \return position of the device in the defined gradient
	 */
	Channel get_position() 
	{
		return channels[0];
	}
	Channel* get_position_ptr()
	{
		return &channels[0];
	}
	void set_position(Channel position)
	{
		if (channels.size() == 0)
		{
			channels.push_back(position);
		}
		else
		{
			channels[0] = position;
		}
	}
private:

};


#endif // !GRADIENT_DEVICE_H

