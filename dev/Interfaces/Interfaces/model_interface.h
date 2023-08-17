/*****************************************************************//**
 * \file   model_interface.h
 * \brief  
 * 
 * \author kason
 * \date   June 2021
 *********************************************************************/
#ifndef COMMAND_MODEL_INTERFACE
#define COMMAND_MODEL_INTERFACE

#include "types/packed_command.h"

/**
 Interfaces for the Model.
 */
class Model_Interfaces {
public:
	class Controller_Interface;
	class Main_Interface;
	class Network_Interface;
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
	static void add_to_step(Packed_Command theCommand);
	/**
	* Request to add a command to the Controller.
	* \param theCommand Command to add to send to the Controller.
	* \param seconds_to_execute  Seconds to append to the current time that the command will run on.
	* \todo Make seconds_to_execute append to current time.
	* \return This should not return anything, but Doxygen thinks it does.
	 */
	static void request_command(Packed_Command theCommand, double seconds_to_execute);

};

/**
 Model interface to the Main Thread.
 */
class Model_Interfaces::Main_Interface
{
public:
	/**
	 * Starts the Model execution loop.
	 */
	static void start_model();
	/**
	 * Stops the Model execution loop.
	 */
	static void stop_model();
};

/**
 Model interface to the Network.
 */
class Model_Interfaces::Network_Interface
{

};

#endif // !MODEL_COMMAND_INTERFACE