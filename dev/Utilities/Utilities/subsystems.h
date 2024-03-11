/*****************************************************************//**
 * \file   subsystems.h
 * \brief  
 * 
 * \author kason
 * \date   March 2024
 *********************************************************************/

#ifndef SUBSYSTEM_BASE_CLASS_H
#define SUBSYSTEM_BASE_CLASS_H
class Subsystem
{
public:
	virtual ~Subsystem();
	virtual void start_loop() = 0;
	virtual void stop_loop() = 0;

	/**
 * \brief Get if subsystem is running.
 *
 * \return if subsystem is running.
 */
	virtual bool is_running() = 0;
	virtual void step() = 0;
	/**
	 * .The string of the namespace name. This is for locating Messages.
	 */
	virtual char* subsystem_name() const = 0;
};

inline Subsystem::~Subsystem()
{

}


#endif