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
#include <mutex>
#include <condition_variable>

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
	virtual void start_clock();

	/**
	 Stop the clock;
	 */
	virtual void stop_clock();
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
	std::chrono::time_point<std::chrono::system_clock> current_time;
	std::chrono::duration<double> elapsed_time;
	std::chrono::duration<double> program_time;
	bool clock_running;

	std::thread timer;
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
		~Timeout();
		bool get_alarm();
		void join();
	private:
		bool alarm;
		double timeout_amount;
		std::condition_variable timer_conditional;
		std::mutex timer_mutex;
	};
}


#endif // !TIMER_H