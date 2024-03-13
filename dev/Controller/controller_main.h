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

#include "system/timer.h"
#include "Messaging/message_relay.h"
#include "Threading/threading.h"
#include "Utilities/subsystems.h"

 /**
  * Main brain of the controller. It keeps track of commands to send to the model, and when to send them
  * \todo Change the timer interface from decrement timer to activate_state timer. This will mainly solve the issues with editing a timeline.
  */
class Controller : public Subsystem
{
public:
	void start_loop();
	void stop_loop();
	bool is_running();
	void step();
	char* subsystem_name() const;

	/**
	 * Singleton get instance
	 * \return Singleton instance
	 */
	static Controller* get_instance();
	/**
	 * Singleton destroy instance
	 */
	static void destroy_instance();
	/**
	* Add a Packed_Command to the sorted queue of commands. Thread safe.
	*
	* \param cmd Command to add
	*/
	void add_command(const Packed_Command& cmd);
private:
	Controller();
	~Controller();

	static Controller* instance;
	/**
	 Is controller loop running
	 */
	std::atomic_bool controller_running;
	/**
	 Sorted queue of commands to send to the model.
	 */
	Command_List controller_queue;
	/**
	 * Task to add the controller to the scheduler.
	 */
	Task controller_task;
};

inline char* Controller::subsystem_name() const
{
	return (char*) "Controller";
}

inline bool Controller::is_running()
{
	return controller_running;
}
/**
 * Get the instance of the controller as an object. This is to convert a namespace to singleton.
 */
#define controller Controller::get_instance()
#endif