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
 *  A Channel device. It contains one channel called Position.
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
	/**
	\return Type of device based off of the DEVICE_IDENTIFIER enum table.
	*/
	virtual DEVICE_IDENTIFIER get_device_type() { return DEVICE_IDENTIFIER::GRADIENT; }
	/**
	 * Return position in the gradient.
	 * \return position of the device in the defined gradient
	 */
	Channel get_position() 
	{
		return channels[0];
	}
	/**
	 Return a pointer to the position.
	 \return Pointer to the position channel for direct manipulation
	 */
	Channel* get_position_ptr()
	{
		return &channels[0];
	}
	/**
	 If the position channel is not created, create it. Otherwise set the position channel to the incoming position.
	 \param position Incoming position to set the position channel.
	 */
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

