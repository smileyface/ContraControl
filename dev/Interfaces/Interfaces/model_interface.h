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
	class Main_Interface;
};

/**
 Model interface to the Controller.
 */
class Model_Interfaces::Controller_Interface {
public:
	/**
	* Add unique commands to the model. Will be run this loop.
	* \param theCommand The command to run with label to device.
	* \return This should not return anything, but Doxygen thinks it does. 
	 */
	static void add_to_step(Model_Command theCommand);
	/**
	* Request to add a command to the Controller.
	* \param theCommand Command to add to send to the Controller.
	* \param seconds_to_execute  Seconds to append to the current time that the command will run on.
	* \todo Make seconds_to_execute append to current time.
	* \return This should not return anything, but Doxygen thinks it does.
	 */
	static void request_command(Model_Command theCommand, double seconds_to_execute);

};

class Model_Interfaces::Main_Interface
{
public:
	static void start_model();
	static void stop_model();
	static void add_view(int view_type);
};

#endif // !MODEL_COMMAND_INTERFACE