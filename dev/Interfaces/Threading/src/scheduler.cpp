#include <chrono>
#include <thread>

#include "Threading/scheduler/scheduler.h"


Scheduler* Scheduler::instance = nullptr;

Scheduler* Scheduler::get_instance()
{
    if(instance == nullptr)
    {
        instance = new Scheduler();
    }
    return instance;
}

void Scheduler::destroy_instance()
{
    if(instance != nullptr)
    {
        delete instance;
        instance = nullptr;
    }
}

void Scheduler::add_task(Task task)
{
    tasks.push(task);
}

int Scheduler::get_number_of_tasks()
{
    return tasks.size();
}

int Scheduler::get_number_of_subtasks()
{
    int total = 0;
    std::priority_queue<Task> task_cpy(tasks);
    while(!task_cpy.empty())
    {
        auto task = task_cpy.top();
        task_cpy.pop();
        total += task.number_of_subtask();
    }
    return total;
}

void Scheduler::start(int frame_rate)
{
    std::chrono::milliseconds frameDurationMs(static_cast<int>(1000.0/ frame_rate));

    
    while(!tasks.empty())
    {
        auto task = tasks.top();
        tasks.pop();
        task.start(frameDurationMs);
        std::this_thread::sleep_for(frameDurationMs);
        task.stop();
    }
}

void Scheduler::stop()
{
    while(!tasks.empty())
    {
        auto task = tasks.top();
        tasks.pop();
        task.stop();
    }
}

Scheduler::Scheduler() :
    frame_rate(30)
{ }

Scheduler::~Scheduler()
{ }
