/*****************************************************************//**
 * \file   device.h
 * \brief  
 * 
 * \author kason
 * \date   May 2021
 *********************************************************************/
#ifndef MAIN_DEVICE_H
#define MAIN_DEVICE_H



#include "Interfaces/types/device_label.h"
#include "Interfaces/types/channel.h"
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
class Device
{
public:
	/** Default constructor */
	Device();
	/**
	 * Constructor that creates number of channels that the device has.
	 *  \param type_of_device Device type for the views.
	 * \param number_of_channels Channels to be added to this device type.
	 */
	Device(DEVICE_IDENTIFIER type_of_device, int number_of_channels);

	~Device();
	/**
	 * \return Numeric ID of the device. This is assigned by the system.
	 */
	Device_Id get_id();
	/**
	 * \return Name of the device. This is mainly for human readability.
	 */
	Device_Name get_name();
	/**
	 * \return Device type + name of the device. This is mainly for human readability and debugging.
	 * \todo move this to an interface
	 */
	virtual Device_Name get_full_name();

	/**
	\return Type of device based off of the DEVICE_IDENTIFIER enum table.
	*/
	virtual DEVICE_IDENTIFIER get_device_type();
	/**
	 * Set the name of the device.
	 * \param new_name Incoming name of device.
	 */
	void set_name(Device_Name new_name);
	/**
	* Set the node ID of the device.
	 * \param new_id Node ID of the device.
	 */
	void set_id(Device_Id new_id);

	/**
	 * Check if type and name is the same
	 * \param ld Device on the left side of the operator.
	 * \return If they're the same.
	 */
	bool operator==(const Device& ld);
	/**
	 \return If device is valid.
	 */
	virtual bool validity_check();
	/**
	 Initalize the device
	 \param name Common name of the device.
	 */
	void initalize(Device_Name name);
	/**
	 Get whether device is on or off.
	 \return if device is powered
	 */
	bool get_power();
	/**
	 Turn on the device.
	 */
	void turn_on();
	/**
	 Turn off the device.
	 */
	void turn_off();	
	/**
	 * Set channel value
	 * \param channel Channel to set the value of.
	 * \param value Value to set Channel to.
	 */
	void set_channel(int channel, Channel value);
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
protected:
	/**
	 ID of the device. This is a system assigned unique id.
	 */
	Device_Id id = INVALID_DEVICE;
	/**
	 Name of device. Mainly for human readability.
	 */
	Device_Name device_name = "INVALID";

	/** Type of device. This is so the UI knows how to handle this device. */
	DEVICE_IDENTIFIER type = DEVICE_IDENTIFIER::DEVICE;
};

#endif
