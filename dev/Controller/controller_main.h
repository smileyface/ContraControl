/*****************************************************************//**
 * \file   controller_main.h
 * \brief  Main brains for the controller. DO NOT INCLUDE. Include a controller_interface instead.
 *
 * \author kason
 * \date   April 2021
 *********************************************************************/

#ifndef MAIN_EXECUTOR_H
#define MAIN_EXECUTOR_H

#include "commander/commander.h"

#include "Interfaces/types/packed_command.h"
#include "system/timer.h"
#include "Messaging/message_relay.h"
#include "Threading/threading.h"

 /**
  * Main brain of the controller. It keeps track of commands to send to the model, and when to send them
  * \todo Change the timer interface from decrement timer to activate_state timer. This will mainly solve the issues with editing a timeline.
  */
namespace controller
{
	/**
	 * .The string of the namespace name. This is for locating Messages.
	 */
	static const char* subsystem_name = "Controller";
	/**
	 Is controller loop running
	 */
	extern bool controller_running;
	/**
	 Sorted queue of commands to send to the model.
	 */
	extern Command_List controller_queue;
	/**
	 * Task to add the controller to the scheduler.
	 */
	extern Task controller_task;

	/**
	 * Start up.
	 *
	 * Resets the Controller clock.
	 */
	void initalize();

	/**
	 * Start the controller loop;
	 */
	void start_controller();

	/**
	 * Add a Packed_Command to the sorted queue of commands. Thread safe.
	 *
	 * \param cmd Command to add
	 */
	void add_command(Packed_Command& cmd);

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