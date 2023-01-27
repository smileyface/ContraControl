/*****************************************************************//**
 * \file   timer.h
 * \brief  
 * 
 * \author kason
 * \date   June 2021
 *********************************************************************/
#ifndef TIMER_H
#define TIMER_H

#include <vector>
#include <thread>

class Timer_Base
{
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
	 Stop the clock;
	 */
	void stop_clock();
	/**
	 \return time since the last update.
	 */
	double get_elapsed_time();
	/**
	 \return how long the program has run. NOTE: Not the system time. System time is not tracked.
	 */
	double get_program_time();

	bool timeout(int timeout_in_millisecond);
protected:
	double current_time;
	double elapsed_time;
	double program_time;
};

namespace Timer
{
	/**
	 A clock for subsystems.
	 */
	class Basic : public Timer_Base
	{
	public:
		Basic();
		~Basic()
		{ };
	};

	class Timeout : public Timer_Base
	{
	public:
		Timeout(int timeout_in_millisecond);

		bool get_alarm();
		void join();
	private:
		bool alarm;
		std::thread timer;
	};
}


#endif // !TIMER_H