#include "../scheduler/threadpool.h"


ThreadPool::ThreadPool() : stop(false)
{
    // Determine the number of threads based on the hardware concurrency
    const size_t numThreads = std::thread::hardware_concurrency();

    for(size_t i = 0; i < numThreads; ++i)
    {
        workers.emplace_back([this]
                             {
                                 while(true)
                                 {
                                     std::function<void()> task;

                                     {
                                         std::unique_lock<std::mutex> lock(queueMutex);

                                         condition.wait(lock, [this]
                                                        {
                                                            return stop || !tasks.empty();
                                                        });

                                         if(stop && tasks.empty())
                                         {
                                             return;
                                         }

                                         task = std::move(tasks.front());
                                         tasks.pop();
                                     }

                                     task_running++;
                                     task();
                                     task_running--;
                                 }
                             });
    }
}


ThreadPool& ThreadPool::getInstance()
{
    static ThreadPool instance;
    return instance;
}

void ThreadPool::sleep_my_thread()
{
    while(tasks.empty() == false || task_running > 0)
    {
        int i = 0;
    }
}

ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        stop = true;
    }

    condition.notify_all();

    for(std::thread& worker : workers)
    {
        worker.join();
    }
}