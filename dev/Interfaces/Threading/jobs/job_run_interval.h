/*****************************************************************//**
 * \file   job_run_interval.h
 * \brief  
 * 
 * \author kason
 * \date   April 2023
 *********************************************************************/

#ifndef THREADING_JOB_RUN_INTERVAL
#define THREADING_JOB_RUN_INTERVAL

class Interval
{
public:
	Interval(int frames_between_runs);
	void update();
	bool run();
private:
	int current_count;
	int total_skip;
};

#endif
