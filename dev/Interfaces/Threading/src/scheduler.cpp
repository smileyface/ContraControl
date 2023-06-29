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

void Scheduler::clean_persistence()
{
    for(std::vector<Task>& task_list : tasks)
    {
        //clean persistence
        for(auto task = task_list.begin(); task != task_list.end(); )
        {
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

void Scheduler::frame_run()
{
    std::chrono::milliseconds frameDurationMs(static_cast<int>(1000.0 / frame_rate));
    while(scheduler_running)
    {
        for(int i = 0; i < tasks.size(); i++)
        {
            for(int j = 0; j < tasks[i].size() && scheduler_running; j++)
            {

                tasks[i][j].start(frameDurationMs);
            }
        }
        std::this_thread::sleep_for(frameDurationMs);
        clean_persistence();
    }
}

void Scheduler::start(int frame_rate)
{
        scheduler_running = true;
        std::thread(&Scheduler::frame_run, this).detach();
}

void Scheduler::stop()
{
    scheduler_running = false;
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
    for(std::vector<Task>& task_list : tasks)
    {
        while(task_list.size() > 0)
            task_list.clear();
    }
}

Scheduler::Scheduler() :
    frame_rate(30),
    scheduler_running(false)
{
    tasks.resize(10);
}

Scheduler::~Scheduler()
{ 
    clear();
}
