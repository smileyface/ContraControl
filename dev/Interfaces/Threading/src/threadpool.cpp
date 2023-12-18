#include "../scheduler/threadpool.h"

#include "Messaging/message_relay.h"

Thread_Pool* Thread_Pool::instance = nullptr;

Thread_Pool::Thread_Pool() : 
    stop(false),
    task_running(0)
{
    // Determine the number of threads based on the hardware concurrency
    const size_t numThreads = 1;

    LOG_INFO("Adding " + std::to_string(numThreads) + " threads", "Scheduler");
    for(size_t i = 0; i < numThreads; ++i)
    {
        workers.emplace_back([this, i]
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
                                     LOG_DEBUG("Thread " + std::to_string(static_cast<int>(i)) + " Running a task");
                                     
                                     task();

                                     task_running--;
                                     LOG_DEBUG("Thread " + std::to_string(static_cast<int>(i)) + " Task complete");
                                 }
                             });
    }
}


Thread_Pool* Thread_Pool::getInstance()
{
    if(instance == nullptr)
    {
        instance = new Thread_Pool();
    }
    return instance;
}

void Thread_Pool::destroy_instance()
{
    if(instance != nullptr)
    {
        LOG_INFO("Destroying Thread Pool", "Scheduler");
        delete instance;
        instance = nullptr;
    }
}
void Thread_Pool::sleep_my_thread()
{
    int i = 0;
    while((tasks.empty() == false || task_running > 0))
    {
        i++;
    }
}

Thread_Pool::~Thread_Pool()
{
    stop = true;
    condition.notify_all();

    for(std::thread& worker : workers)
    {
        if(worker.joinable())
        {
            worker.join();
        }
    }
    workers.clear();
}