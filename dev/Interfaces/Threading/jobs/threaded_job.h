/*****************************************************************//**
 * \file   subsystem_job.h
 * \brief  
 * 
 * \author kason
 * \date   March 2023
 *********************************************************************/

#ifndef THREAD_POOL_SUBSYSTEM_JOBS
#define THREAD_POOL_SUBSYSTEM_JOBS


#include <vector>
#include <functional>

#include "job_run_interval.h"

typedef std::function<void()> Job;

class Threaded_Job
{
public:
	Threaded_Job();
	Threaded_Job(Job job);
	Threaded_Job(Job job, Interval interval);
	void run();
private:
	Job job_list;
	Interval run_interval;
};

struct Frame
{
	float frame_percentage;
	std::vector<Threaded_Job> job_list;
};


#endif
