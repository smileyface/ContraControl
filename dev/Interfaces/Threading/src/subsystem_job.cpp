#include "../subsystem_job.h"

Thread_Frame::Thread_Frame()
{
}

Threaded_Job Thread_Frame::next_job()
{
	Threaded_Job current_job = job_list.front();
	job_list.erase(job_list.begin());
	return current_job;
}

void Subsystem_Threaded_Frame::add_subframe(Thread_Frame* subframe)
{
	subframes.push_back(subframe);
}

void Subsystem_Threaded_Frame::setup_job_list()
{
	for(auto frame : subframes)
	{
		frame->setup_job_list();
		auto frame_job_list = frame->get_job_list();
		job_list.insert(job_list.end(), frame_job_list.begin(), frame_job_list.end());
	}
}
