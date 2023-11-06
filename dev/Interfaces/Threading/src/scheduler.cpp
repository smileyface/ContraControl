#include <chrono>
#include <thread>

#include "Threading/scheduler/scheduler.h"
#include "Threading/scheduler/threadpool.h"
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
    Thread_Pool::destroy_instance();
}

void Scheduler::clean_persistence()
{
    for(std::vector<Task*>& task_list : tasks)
    {
        //clean persistence
        for(auto task = task_list.begin(); task != task_list.end(); )
        {
            if((*task)->get_persistence() == false)
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

void Scheduler::add_task(Task* task)
{
    if(task->get_priority() < 1 || task->get_priority() > 10)
    {
        LOG_ERROR("Task priority outside of range", "Scheduler");
        return;
    }
    tasks[task->get_priority() - 1].push_back(task);
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
            total += task->number_of_subtask();
        }
    }
    return total;
}

int Scheduler::get_overruns()
{
    return overruns;
}

void Scheduler::frame(std::chrono::milliseconds frameDurationMs)
{
    LOG_DEBUG("Frame Beginning");
    for(int i = 0; i < tasks.size(); i++)
    {
        //Start the tasks for this priority of the frame.
        for(int j = 0; j < tasks[i].size(); j++)
        {
            tasks[i][j]->start(frameDurationMs);
        }
        //Wait for the tasks of this priority to finish running
        Thread_Pool::getInstance()->sleep_my_thread();
        //Clean up the tasks for this priority of the frame.
        for(int j = 0; j < tasks[i].size(); j++)
        {
            tasks[i][j]->stop();
        }
    }
    LOG_DEBUG("Frame End");
    clean_persistence();
}

void Scheduler::add_system_task(std::function<void()> task)
{
    system_task.add_subtask(Sticky_Task(task));
}

void Scheduler::add_cleanup_task(std::function<void()> task)
{
    cleanup_task.add_subtask(Sticky_Task(task));
}

void Scheduler::start(int frameDuration) {
    scheduler_running = true;
    frame_rate = frameDuration;
    int frames_run = 0;
    scheduler_thread = std::thread([ &frames_run, this] ()
                {
                    frames_run = 0;
                    LOG_INFO("Scheduler Start", "Scheduler");
                    std::chrono::milliseconds frameDurationMs(static_cast<int>((1000.0/frame_rate)));

                    auto start_time = std::chrono::steady_clock::now();
                    auto cur_time = start_time;
                    while(scheduler_running)
                    {
                        start_time = std::chrono::steady_clock::now();
                        frame(frameDurationMs);
                        cur_time = std::chrono::steady_clock::now();
                        auto elapsedSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(cur_time - start_time);

                        if(elapsedSeconds > frameDurationMs)
                        {
                            overruns++;
                            LOG_ERROR("OVERRUN", "Scheduler");
                        }
                        else
                        {
                            std::this_thread::sleep_for(frameDurationMs - (elapsedSeconds));
                        }
                        frames_run++;
                    }
                    LOG_INFO("Scheduler Dead", "Scheduler");
                });
}

void Scheduler::stop()
{
    scheduler_running = false;
    for(int i = 0; i < tasks.size(); i++)
    {
        for(int j = 0; j < tasks[i].size(); j++)
        {
            tasks[i][j]->stop();
        }
    }
    if(scheduler_thread.joinable())
    {
        scheduler_thread.join();
    }
}

void Scheduler::clear()
{
    for(std::vector<Task*>& task_list : tasks)
    {
        while(task_list.size() > 0)
            task_list.clear();
    }
}

Scheduler::Scheduler() :
    overruns(0),
    frame_rate(30),
    scheduler_running(false)
{
    tasks.resize(10);

    system_task = Task("System", 1, .05, true, false);
    add_task(&system_task);
    cleanup_task = Task("System Cleanup", 5, .05, true, false);
    add_task(&cleanup_task);
}

Scheduler::~Scheduler()
{ 
    clear();
}
