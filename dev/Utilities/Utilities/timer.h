/*****************************************************************//**
 * \file   timer.h
 * \brief  
 * 
 * \author kason
 * \date   June 2021
 *********************************************************************/
#ifndef TIMER_H
#define TIMER_H


/**
 A clock for subsystems.
 */
class Timer {
public:
	/**
	 Update the elapsed and program time.
	 */
	void update_time();
	/**
	 Reset program clock
	 */
	void reset_clock();
	/**
	 move the current program time.
	 */
	void start_clock();
	/**
	 \return time since the last update.
	 */
	double get_elapsed_time();
	/**
	 \return how long the program has run. NOTE: Not the system time. System time is not tracked. 
	 */
	double get_program_time();

	bool timeout(int timeout_in_millisecond);

	Timer();
	~Timer() {};

private:
	double current_time;
	double elapsed_time;
	double program_time;
};

#endif // !TIMER_H