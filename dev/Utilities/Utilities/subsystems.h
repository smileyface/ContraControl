/*****************************************************************//**
 * \file   subsystems.h
 * \brief  
 * 
 * \author kason
 * \date   March 2024
 *********************************************************************/

#ifndef SUBSYSTEM_BASE_CLASS_H
#define SUBSYSTEM_BASE_CLASS_H
/**
 * A parent class for all the subsystems.
 */
class Subsystem
{
public:
	virtual ~Subsystem();
	/**
	 * \brief Start up the Subsystem loop.
	 *
	 * Spawns a thread for the Subsystem to be run in.
	 */
	virtual void start_loop() = 0;
	/**
	 * \brief Start shutting down the Subsystem.
	 *
	 * Shuts down the Subsystem execution loop.
	 */
	virtual void stop_loop() = 0;
	/**
	 * \brief Get if subsystem is running.
	 *
	 * \return if subsystem is running.
	 */
	virtual bool is_running() = 0;
	/**
	*\brief Run all commands lined up for this iteration of the loop.
	*
	* This is the main function of a loop.
	*/
	virtual void step() = 0;
	/**
	 * \return The string of the namespace name. This is for locating Messages.
	 */
	virtual char* subsystem_name() const = 0;
};

inline Subsystem::~Subsystem()
{

}


#endif