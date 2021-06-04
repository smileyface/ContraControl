/*****************************************************************//**
 * \file   controller_main.h
 * \brief  Main brains for the controller. DO NOT INCLUDE. Include a controller_interface instead.
 * 
 * \author kason
 * \date   April 2021
 *********************************************************************/


#ifndef MAIN_EXECUTOR_H
#define MAIN_EXECUTOR_H



#include "Interfaces/types/timed_command.h"
#include "system/timer.h"

/**
 * Main brain of the controller. It keeps track of commands to send to the model, and when to send them
 * \todo Create a threaded looping function that will step through commands.
 */
namespace controller
{
	/**
	 Is controller loop running
	 */
	extern bool controller_running;
	/**
	 Sorted queue of commands to send to the model.
	 */
	extern Timed_List controller_queue;

	/**
	 * Start up.
	 * 
	 * Resets the Controller clock.
	 */
	void initalize();

	/**
	 * Add a Timed_Command to the sorted queue of commands.
	 * 
	 * \param tc Command to add
	 */
	void add_command(Timed_Command tc);

	/**
	 * Iterate the loop.
	 * 
	 */
	void step();

	/**
	 * Start shutting down the controller.
	 */
	void stop_controller();
	/**
	 * Clear queues
	 */
	void clean_up();
}



#endif