/*****************************************************************//**
 * \file   controller_interface.h
 * \brief  
 * 
 * \author kason
 * \date   June 2021
 *********************************************************************/
#ifndef MODEL_CONTROLLER_INTERFACE_H
#define MODEL_CONTROLLER_INTERFACE_H


#include "types/timed_command.h"

/**
 Interfaces for the Controller.
 */
class Controller_Interfaces {
public:
	class Model_Interface;

};

/**
 Controller interface to the Model
 */
class Controller_Interfaces::Model_Interface {
public:
	/**
		Send a command to the model.
		\param timed_command Command to send to the model.
	 */
	static void send_command(Timed_Command timed_command);

	/**
		 Add command to the controller timeline.
		 \param timed_command Command to add to the timeline.
	 */
	static void request_command_add(Timed_Command timed_command);

	/**
	  Get device pointer from the model
	  \param label Label to the device.
	  \return Pointer to the Device. 
	 */
	template <class Device_Template>
	static Device_Template* get_device_from_model(Device_Label label);
};

#endif // !MODEL_CONTROLLER_INTERFACE_H