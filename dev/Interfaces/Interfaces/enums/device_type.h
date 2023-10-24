/*****************************************************************//**
 * \file   device_type.h
 * \brief  
 * 
 * \author kason
 * \date   August 2023
 *********************************************************************/
#ifndef MODEL_DEVICE_TYPE_ENUM
#define MODEL_DEVICE_TYPE_ENUM

#include "Interfaces/types/device_label.h"

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
	 A 3 channel color device
	 */
	RGB,
	/**
	Device that controls audio
	*/
	AUDIO,
	/**
	 An invalid device. Either uninitalized or removed.
	 */
	INVALID
};
#endif // !MODEL_DEVICE_TYPE_ENUM
