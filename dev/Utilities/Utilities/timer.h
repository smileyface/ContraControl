/*****************************************************************//**
 * \file   timer.h
 * \brief  
 * 
 * \author kason
 * \date   June 2021
 *********************************************************************/
#ifndef TIMER_H
#define TIMER_H

#include <ctime>

/**
 A clock for subsystems.
 */
class Timer {
public:
	/**
	 Update the elapsed and program time.
	 */
	void update_time() 
	{
		elapsed_time = (std::clock() - current_time) / (double)CLOCKS_PER_SEC;
		program_time += elapsed_time;
		current_time = std::clock();
	}
	/**
	 Reset program clock
	 */
	void reset_clock() 
	{
		elapsed_time = 0.0;
		current_time = std::clock();
		program_time = 0.0;
	}
	/**
	 move the current program time.
	 */
	void start_clock() 
	{
		current_time = std::clock();
	}
	/**
	 \return time since the last update.
	 */
	double get_elapsed_time() { return elapsed_time; }
	/**
	 \return how long the program has run. NOTE: Not the system time. System time is not tracked. 
	 */
	double get_program_time() { return program_time; }

	Timer() {};
	~Timer() {};

private:
	double current_time = std::clock();
	double elapsed_time = 0.0;
	double program_time = 0.0;
};

#endif // !TIMER_H