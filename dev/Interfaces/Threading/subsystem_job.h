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

typedef std::function<void()> Threaded_Job;

enum class FRAME_SOURCE
{
	NETWORK,
	VIEW_SUBSYSTEM,
	MODEL,
	CONTROL,
	MESSAGE_RELAY
};

class Thread_Frame
{
public:
	Thread_Frame();
	Threaded_Job next_job();
	virtual void setup_job_list() = 0;
	std::vector<Threaded_Job> get_job_list();
protected:
	std::vector<Threaded_Job> job_list;
	FRAME_SOURCE source;
};

class Subsystem_Threaded_Frame : protected Thread_Frame
{
public:
	bool frame_overrun(int frame_rate_HZ);
	virtual void setup_job_list();
	void add_subframe(Thread_Frame* subframe);
protected:
	float frame_percentage_limit;
	time_t run_time;
	std::vector<Thread_Frame*> subframes;
};

#endif
