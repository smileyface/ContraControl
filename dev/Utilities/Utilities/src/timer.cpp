#include "../timer.h"

#include <ctime>

Timer::Timer()
{
	current_time = std::clock();
	elapsed_time = 0.0;
	program_time = 0.0;
}


void Timer::update_time()
{
	elapsed_time = (std::clock() - current_time) / (double) CLOCKS_PER_SEC;
	program_time += elapsed_time;
	current_time = std::clock();
}

void Timer::reset_clock()
{
	elapsed_time = 0.0;
	current_time = std::clock();
	program_time = 0.0;
}

void Timer::start_clock()
{
	current_time = std::clock();
}

double Timer::get_elapsed_time()
{
	return elapsed_time;
}

double Timer::get_program_time()
{
	return program_time;
}

bool Timer::timeout(int timeout_in_millisecond)
{
	update_time();
	//return if the alarm went off
	return program_time > (timeout_in_millisecond / 1000.0);
}
