/*****************************************************************//**
 * \file   switch.h
 * \brief  
 * 
 * \author kason
 * \date   June 2021
 *********************************************************************/
#ifndef SWITCH_DEVICE_H
#define SWITCH_DEVICE_H

#include "device.h"

/**
 A boolean based device. 
 */
class Switch_Device: public Device
{
public:
	Switch_Device() { };
	~Switch_Device() {};
	virtual DEVICE_IDENTIFIER get_device_type() { return DEVICE_IDENTIFIER::SWITCH; }



private:

};

#endif // !SWITCH_DEVICE_H