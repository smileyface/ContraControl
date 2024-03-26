/*****************************************************************//**
 * \file   controller_main.h
 * \brief  Main brains for the controller. DO NOT INCLUDE. Include a controller_interface instead.
 *
 * \author kason
 * \date   April 2021
 *********************************************************************/

#ifndef MAIN_EXECUTOR_H
#define MAIN_EXECUTOR_H

#include <memory>

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
	/**
	 * Singleton get instance
	 * \return Singleton instance
	 */
	static Controller* get_instance();
	/**
	 * Singleton destroy instance
	 */
	static void destroy_instance();

	void start_loop() override;
	void stop_loop() override;
	void step() override;
	char* subsystem_name() const override; // Added accessor for subsystem name
	bool is_running() override; // Added method to check if the controller is running


	/**
	 * \brief Add a command to run through the controller.
	 *
	 * \param cmd Reference to the command to add to the controller.
	 */
	void add_command(const Packed_Command& cmd); 
private:
	Controller();
	~Controller();
	static Controller* instance;

	Task controller_task;
	std::vector<Packed_Command> controller_queue;
	std::mutex controller_mutex;
	Timer controller_timer;
	bool controller_running = false;

	// Cleanup task function
	void cleanup_task();

	// Prevent copy construction and assignment
	Controller(const Controller&) = delete;
	Controller& operator=(const Controller&) = delete;
};

inline bool Controller::is_running()
{
	return controller_running;
}
/**
 * Get the instance of the controller as an object. This is to convert a namespace to singleton.
 */
#define controller Controller::get_instance()
#endif