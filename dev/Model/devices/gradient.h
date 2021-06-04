/*****************************************************************//**
 * \file   gradient.h
 * \brief  
 * 
 * \author kason
 * \date   May 2021
 *********************************************************************/
#ifndef GRADIENT_DEVICE_H
#define GRADIENT_DEVICE_H

#include "device.h"

/** 
 *  A non-binary device.
 */
class Gradient_Device: public Device
{
public:
	Gradient_Device() {};
	~Gradient_Device() {};
	/**
	 * Return position in the gradient.
	 * \return position of the device in the defined gradient
	 */
	float get_position() 
	{
		return state.position;
	}

private:

};


#endif // !GRADIENT_DEVICE_H

