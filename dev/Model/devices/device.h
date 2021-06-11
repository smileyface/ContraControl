/*****************************************************************//**
 * \file   device.h
 * \brief  
 * 
 * \author kason
 * \date   May 2021
 *********************************************************************/

#ifndef MAIN_DEVICE_H
#define MAIN_DEVICE_H

#include <typeinfo> //typeid

#include "../states.h"

/*!
 * \cond
 */
static uint16_t device_id_pool = 0;
/*!
 *  \endcond
 * An output.
 */
class Device
{
public:
	Device() {};
	~Device() {};
	/**
	 * \return Numeric ID of the device. This is assigned by the system.
	 */
	Device_Id get_id()
	{
		return id;
	};
	/**
	 * \return Name of the device. This is mainly for human readability.
	 */
	Device_Name get_name()
	{
		return device_name;
	};
	/**
	 * \return Device type + name of the device. This is mainly for human readability and debugging.
	 */
	virtual Device_Name get_full_name()
	{
		Device_Name device_name = typeid(*this).name();
		return device_name.erase(0, 6) + "::" + get_name();
	}
	/**
	 * Set the name of the device.
	 * \param new_name Incoming name of device.
	 */
	void set_name(Device_Name new_name)
	{
		device_name = new_name;
	}
	/**
	* Set the node ID of the device.
	 * \param new_id Node ID of the device.
	 */
	void set_id(Device_Id new_id)
	{
		id = new_id;
	}

	/**
	 * Get state of device.
	 * \return state of device packed in a char
	 */
	unsigned char get_state_switches()
	{
		return state.switches_pack();
	}

	/**
	 * Check if type and name is the same
	 * \param ld Device on the left side of the operator.
	 * \return If they're the same.
	 */
	bool operator==(const Device& ld)
	{
		bool type_check = typeid(*this).name() == typeid(ld).name();
		bool device_name = this->device_name == ld.device_name;
		return type_check && device_name;
	}
	/** 
	State of the device. 
	 */
	Device_State state;
protected:
	/**
	 ID of the device. This is a system assigned unique id.
	 */
	Device_Id id = INVALID_DEVICE;
	/**
	 Name of device. Mainly for human readability.
	 */
	Device_Name device_name = "INVALID";
};


#endif
