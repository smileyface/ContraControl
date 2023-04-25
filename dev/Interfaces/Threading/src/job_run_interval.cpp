#include "../jobs/job_run_interval.h"

Interval::Interval(int frames_between_runs) :
	total_skip(frames_between_runs),
	current_count(0)
{
}

void Interval::update()
{
	current_count++;
}

bool Interval::run()
{
	bool interval_complete = false;
	if(current_count == total_skip)
	{
		interval_complete = true;
	}
	if(interval_complete)
	{
		current_count = 0;
	}
	return interval_complete;
}
