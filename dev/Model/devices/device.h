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

#include "Interfaces/types/device_label.h"
#include "Interfaces/types/channel.h"

#include "Interfaces/types/view_capable.h"
 /**
  *  A list of types of devices.
  */
enum class DEVICE_IDENTIFIER : Device_Id
{
	/**
	Generic Device.
	*/
	DEVICE,
	/**
	Device that is binary.
	*/
	SWITCH,
	/**
	Device that has one channel that has various positions.
	*/
	GRADIENT,
	/**
	Device with multiple channels
	*/
	CHANNEL,
	/**
	Device that controls audio
	*/
	AUDIO
};
/*!
 * \cond
 */
static uint16_t device_id_pool = 0;
/*!
 *  \endcond
 * An output.
 */
class Device : public View_Capable
{
public:
	Device() { };
	Device(DEVICE_IDENTIFIER type_of_device, int number_of_channels)
	{
		type = type_of_device;
		for (int i = 0; i < number_of_channels; i++)
		{
			channels.push_back(UNUSED);
		}
	}
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
	 * \todo move this to an interface
	 */
	virtual Device_Name get_full_name()
	{
		Device_Name device_name = typeid(*this).name();
		return device_name.erase(0, 6) + "::" + get_name();
	}

	/**
	\return Type of device based off of the DEVICE_IDENTIFIER enum table.
	*/
	virtual DEVICE_IDENTIFIER get_device_type() { return type; }
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
	 \return If device is valid.
	 */
	virtual bool validity_check()
	{
		return true;
	}
	/**
	 Initalize the device
	 \param name Common name of the device.
	 */
	void initalize(Device_Name name)
	{
		device_name = name;
		initalized = true;
		valid = validity_check();
	}
	/**
	 Get whether device is on or off.
	 \return if device is powered
	 */
	bool get_power()
	{
		return power;
	}
	/**
	 Turn on the device.
	 */
	void turn_on()
	{
		if (initalized == false)
		{
			valid = false;
			return;
		}
		power = true;
	}
	/**
	 Turn off the device.
	 */
	void turn_off()
	{
		if (initalized == false)
		{
			valid = false;
			return;
		}
		power = false;
	}
	/**
	 Has the device been initalized.
	 */
	bool initalized = false;
	/**
	 Power state for the device.
	 */
	bool power = false;
	/**
	Validity bit for the device.
	 */
	bool valid = false;
	/**
	 Position of each channel. 1-255 range. 0 is reserved for unused channels
	*/
	std::vector<Channel> channels;

	/**
	 * Set channel value
	 */
	void set_channel(int channel, Channel value)
	{
		channels[channel] = value;
	}
protected:
	/**
	 ID of the device. This is a system assigned unique id.
	 */
	Device_Id id = INVALID_DEVICE;
	/**
	 Name of device. Mainly for human readability.
	 */
	Device_Name device_name = "INVALID";

	DEVICE_IDENTIFIER type = DEVICE_IDENTIFIER::DEVICE;
};

#endif
