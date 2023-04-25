/*****************************************************************//**
 * \file   threading.h
 * \brief  
 * 
 * \author kason
 * \date   March 2023
 *********************************************************************/

#ifndef THREAD_POOL
#define THREAD_POOL

#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

#include "jobs/threaded_job.h"


class Thread_Pool
{
public:

	~Thread_Pool();

	static Thread_Pool* get_instance();
	static void destroy_instance();

	void update_thread_count(int thread_count);
	void add_job(const std::function<void()>& job);
	int number_of_threads();
	bool running();
private:
	const unsigned char MAX_THREAD_AMOUNT = 100;

	std::mutex queue_mutex;                  // Prevents data races to the job queue
	std::condition_variable mutex_condition; // Allows threads to wait on new jobs or termination 

	std::queue<Threaded_Job> job_queue;
	std::vector<std::thread> pool;
	std::vector<bool> pool_running;
	static Thread_Pool* instance;

	Thread_Pool();
	void threading_loop(int thread_number);
};

#endif // !THREAD_POOL