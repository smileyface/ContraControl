#include <chrono>
#include <thread>

#include "Threading/scheduler/scheduler.h"
#include "Messaging/message_relay.h"


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
    if(task.get_priority() < 1 || task.get_priority() > 10)
    {
        LOG_ERROR("Task priority outside of range", "Adding task");
        return;
    }
    tasks[task.get_priority() - 1].push_back(task);
}

int Scheduler::get_number_of_tasks()
{
    int total = 0;
    for(auto task_list : tasks)
    {
            total += task_list.size();
    }
    return total;
}

int Scheduler::get_number_of_subtasks()
{
    int total = 0;

    for(auto task_list : tasks)
    {
        for(auto task : task_list)
        {
            total += task.number_of_subtask();
        }
    }
    return total;
}

void Scheduler::start(int frame_rate)
{
    std::chrono::milliseconds frameDurationMs(static_cast<int>(1000.0/ frame_rate));

    for(std::vector<Task>& task_list : tasks)
    {
        
        for(auto task = task_list.begin(); task != task_list.end(); )
        {
            task->start(frameDurationMs);
            std::this_thread::sleep_for(frameDurationMs);
            task->stop();
            if(task->get_persistence() == false)
            {
                task = task_list.erase(task);
            }
            else
            {
                ++task;
            }
        }
    }
}

void Scheduler::stop()
{
    for(int i = 0; i < tasks.size(); i++)
    {
        for(int j = 0; j < tasks[i].size(); j++)
        {
            tasks[i][j].stop();
        }
    }
}

void Scheduler::clear()
{
    for(int i = 0; i < tasks.size(); i++)
    {
        tasks[i].clear();
    }
}

Scheduler::Scheduler() :
    frame_rate(30)
{
    tasks.resize(10);
}

Scheduler::~Scheduler()
{ 
    clear();
}
