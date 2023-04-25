/*****************************************************************//**
 * \file   scheduler.h
 * \brief  
 * 
 * \author kason
 * \date   April 2023
 *********************************************************************/

#include <map>

#include "../jobs/threaded_job.h"

enum class FRAME_SOURCE
{
	MAIN,
	NETWORK,
	MODEL,
	VIEW_SUBSYSTEM,
	CONTROL,
	MESSAGE_RELAY
};

class Scheduler
{
public:
	static Scheduler* get_instance();

	void add_job_to_frame(FRAME_SOURCE source, Threaded_Job job);
	void add_job_to_frame(FRAME_SOURCE source, Threaded_Job job, Interval interval);
private:
	Scheduler();
	static Scheduler* instance;

	std::map<FRAME_SOURCE, Frame> frame;
	float refresh_rate;
};