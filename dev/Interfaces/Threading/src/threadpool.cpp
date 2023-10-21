#include "../scheduler/threadpool.h"

Thread_Pool* Thread_Pool::instance = nullptr;

Thread_Pool::Thread_Pool() : stop(false)
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
        delete instance;
        instance = nullptr;
    }
}
void Thread_Pool::sleep_my_thread()
{
    while(tasks.empty() == false || task_running > 0)
    {
        int i = 0;
    }
}

Thread_Pool::~Thread_Pool()
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