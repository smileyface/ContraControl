#include "../timer.h"

#include <ctime>
#include <chrono>
#include <iostream>


Timer::Timeout::~Timeout()
{
	join();
}

void Timer_Base::update_time()
{
	auto captured_time = std::chrono::system_clock::now();
	elapsed_time = captured_time - current_time;
	program_time += elapsed_time;
	current_time = captured_time;
}

void Timer_Base::reset_clock()
{
	elapsed_time = std::chrono::duration<double>(0);
	current_time = std::chrono::system_clock::now();
	program_time = std::chrono::duration<double>(0);
}

void Timer_Base::start_clock()
{
	current_time = std::chrono::system_clock::now();
	clock_running = true;
}

void Timer_Base::stop_clock()
{
	update_time();
	clock_running = false;
}

double Timer_Base::get_elapsed_time()
{
	return elapsed_time.count();
}

double Timer_Base::get_program_time()
{
	return program_time.count();
}

Timer::Basic::Basic()
{
	reset_clock();
}


Timer::Timeout::Timeout(int timeout_in_millisecond)
{ 
	alarm = false;
	reset_clock();
	timeout_amount = timeout_in_millisecond / (double)CLOCKS_PER_SEC;

}

bool Timer::Timeout::get_alarm()
{
	update_time();
	return program_time.count() > timeout_amount;
}


void Timer::Timeout::join()
{ 
	while(!get_alarm() && clock_running)
	{
		update_time();
	}
}
