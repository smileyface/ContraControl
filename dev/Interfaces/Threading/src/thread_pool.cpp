#include "../thread_pool.h"

#include <mutex>


Thread_Pool* Thread_Pool::instance = nullptr;

Thread_Pool::Thread_Pool()
{}

Thread_Pool::~Thread_Pool()
{
	update_thread_count(0);
}

Thread_Pool* Thread_Pool::get_instance()
{
	if(instance == nullptr)
	{
		instance = new Thread_Pool();
	}
	return instance;
}
void Thread_Pool::destroy_instance()
{
	delete instance;
}

bool Thread_Pool::running()
{
	return pool.size() != 0 && pool_running.size() != 0;
}

void Thread_Pool::update_thread_count(int thread_count)
{
	for(int i = pool.size(); i < thread_count; i++)
	{
		pool_running.push_back(true);
		pool.push_back(std::thread(&Thread_Pool::threading_loop, this, i));
	}
	for(int i = pool.size(); i > thread_count; i--)
	{
		pool_running[i-1] = false;
		mutex_condition.notify_all();
		if(pool.back().joinable())
		{
			pool.back().join();
		}
		pool_running.pop_back();
		pool.pop_back();
	}
}

void Thread_Pool::threading_loop(int thread_number)
{
	while(pool_running[thread_number])
	{
		Threaded_Job job;
		{
			std::unique_lock<std::mutex> lock(queue_mutex);
			mutex_condition.wait(lock, [this, thread_number]
								 {
									 return !job_queue.empty() || !pool_running[thread_number];
								 });
			if(!pool_running[thread_number])
			{
				return;
			}
			job = job_queue.front();
			job_queue.pop();
		}
		job.run();
	}
}

void Thread_Pool::add_job(const std::function<void()>& job)
{
	{
		std::unique_lock<std::mutex> loc(queue_mutex);
		job_queue.push(job);
	}
	mutex_condition.notify_one();
}

int Thread_Pool::number_of_threads()
{
	return pool.size();
}
