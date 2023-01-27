#include "../timer.h"

#include <ctime>
#include <chrono>




void Timer_Base::update_time()
{
	elapsed_time = (std::clock() - current_time) / (double) CLOCKS_PER_SEC;
	program_time += elapsed_time;
	current_time = std::clock();
}

void Timer_Base::reset_clock()
{
	elapsed_time = 0.0;
	current_time = std::clock();
	program_time = 0.0;
}

void Timer_Base::start_clock()
{
	current_time = std::clock();
}

void Timer_Base::stop_clock()
{
	elapsed_time = (std::clock() - current_time) / (double) CLOCKS_PER_SEC;
	program_time += elapsed_time;
}

double Timer_Base::get_elapsed_time()
{
	return elapsed_time;
}

double Timer_Base::get_program_time()
{
	return program_time;
}

Timer::Basic::Basic()
{
	current_time = std::clock();
	elapsed_time = 0.0;
	program_time = 0.0;
}

Timer::Timeout::Timeout(int timeout_in_millisecond)
{ 
	alarm = false;
	program_time = 0.0;
	start_clock();
	timer = std::thread([this, timeout_in_millisecond] () mutable
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(timeout_in_millisecond));
					alarm = true;
					stop_clock();
				});
}

bool Timer::Timeout::get_alarm()
{
	return alarm;
}

void Timer::Timeout::join()
{ 
	if(timer.joinable())
	{
		timer.join();
	}
}
