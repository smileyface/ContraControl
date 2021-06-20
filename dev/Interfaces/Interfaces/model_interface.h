/*****************************************************************//**
 * \file   model_interface.h
 * \brief  
 * 
 * \author kason
 * \date   June 2021
 *********************************************************************/
#ifndef COMMAND_MODEL_INTERFACE
#define COMMAND_MODEL_INTERFACE

#include "types/model_command.h"

/**
 Interfaces for the Model.
 */
class Model_Interfaces {
public:
	class Controller_Interface;
};

/**
 Model interface to the Controller.
 */
class Model_Interfaces::Controller_Interface {
public:
	/**
	 Add unique commands to the model. Will be run this loop.
	 \param theCommand The command to run with label to device.
	 */
	static void add_to_step(Model_Command theCommand);
	/**
	 Request to add a command to the Controller.
	 \param theCommand Command to add to send to the Controller.
	 \param seconds_to_execute  Seconds to append to the current time that the command will run on.
	 \todo Make seconds_to_execute append to current time.
	 */
	static void request_command(Model_Command theCommand, double seconds_to_execute);

	/**
	 Get pointer to device by given label.
	 \param label The Device_Label that maps to the desired device.
	 \return Desired device.
	 */
	template <class Device_Template>
	static Device_Template* get_device(Device_Label label);

};

#endif // !MODEL_COMMAND_INTERFACE