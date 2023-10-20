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
  * @brief The ThreadPool class represents a thread pool for concurrent task execution.
  */
class ThreadPool
{
public:
    /**
     * @brief Get the singleton instance of the ThreadPool.
     * @return The ThreadPool instance.
     */
    static ThreadPool& getInstance();

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    /**
     * @brief Enqueue a task for execution in the thread pool.
     * @tparam F The type of the task to be enqueued.
     * @param task The task to be enqueued for execution.
     */
    template <class F>
    void enqueue(F&& task)
    {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            tasks.emplace((task));
        }
        condition.notify_one();
    }

    /**
     * Sleep the current thread with a spin lock until all threads have finished executing and all queued up jobs are run.
     */
    void sleep_my_thread();

    ~ThreadPool();

private:
    ThreadPool();

    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queueMutex;
    std::condition_variable condition;

    std::atomic_bool stop;
    std::atomic_char task_running;
};

#endif // THREADPOOL_H