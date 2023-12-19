/*****************************************************************//**
 * \file   threadpool.h
 * \brief  
 * 
 * \author kason
 * \date   October 2023
 *********************************************************************/

#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>

 /**
  * @brief The Thread_Pool class represents a thread pool for concurrent task execution.
  */
class Thread_Pool
{
public:
    /**
     * @brief Get the singleton instance of the Thread_Pool.
     * @return The Thread_Pool instance.
     */
    static Thread_Pool* getInstance();

    /**
     * @brief Destroy the singleton instance of the Thread_Pool.
     * 
     */
    static void destroy_instance();

    Thread_Pool(const Thread_Pool&) = delete;
    Thread_Pool& operator=(const Thread_Pool&) = delete;

    /**
     * @brief Enqueue a task for execution in the thread pool.
     * @tparam F The type of the task to be enqueued.
     * @param task The task to be enqueued for execution.
     */
    template <class F>
    void enqueue(F&& task)
    {
        {
            const std::lock_guard<std::mutex> lock(queueMutex);
            tasks.emplace((task));
        }
        condition.notify_one();
    }

    /**
     * Sleep the current thread with a spin lock until all threads have finished executing and all queued up jobs are run.
     */
    void sleep_my_thread();

    ~Thread_Pool();

private:
    Thread_Pool();

    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queueMutex;
    std::condition_variable condition;

    std::atomic_bool stop;
    std::atomic_char task_running;

    static Thread_Pool* instance;
};

#endif // THREADPOOL_H