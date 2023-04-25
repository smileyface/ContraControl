#include "../jobs/threaded_job.h"

Threaded_Job::Threaded_Job() :
	job_list(nullptr),
	run_interval(0)
{

}

Threaded_Job::Threaded_Job(Job job) :
	job_list(job),
	run_interval(0)
{

}

Threaded_Job::Threaded_Job(Job job, Interval interval) :
	job_list(job),
	run_interval(interval)
{

}

void Threaded_Job::run()
{
	if(run_interval.run())
	{
		job_list();
	}
}
