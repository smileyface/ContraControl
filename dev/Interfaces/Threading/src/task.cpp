#include "../scheduler/task.h"

#include "../scheduler/threadpool.h"

#include <iostream>
#include <map>
#include <mutex>

std::mutex g_pages_mutex;

int alive_threads = 0;

bool* FALSE = new bool(false);
bool* TRUE = new bool(true);

Task::Task(const std::string& name, int priority, double percentage, bool persistence, bool clear_subtasks) :  
    name(name),
    priority(priority),
    percentage(percentage),
    is_running(false),
    persistence(persistence),
    overruns(0),
    clear_subtasks(clear_subtasks)
{ }

Task::Task(const std::string& name, int priority, double percentage, bool persistence = false) :
    name(name),
    priority(priority),
    percentage(percentage),
    is_running(false),
    persistence(persistence),
    overruns(0),
    clear_subtasks(true)
{ }

Task::Task(const std::string& name, int priority, double percentage) :
    name(name),
    priority(priority),
    percentage(percentage),
    is_running(false),
    persistence(true),
    overruns(0),
    clear_subtasks(true)
{ }

Task::Task(const Task& other) :
    name(other.name), 
    priority(other.priority), 
    percentage(other.percentage), 
    is_running(false), 
    persistence(other.persistence),
    subtasks(other.subtasks),
    overruns(other.overruns),
    clear_subtasks(other.clear_subtasks)
{ }

Task::Task() :
    name(""),
    priority(0),
    percentage(0.0),
    is_running(false),
    persistence(false),
    subtasks({}),
    overruns(0),
    clear_subtasks(true)
{ }

Task::~Task()
{
    stop();
}

void Task::add_subtask(const Subtask& subtask)
{
    subtasks.push_back(subtask);
}

void Task::add_subtask(const std::function<void()>& subtask)
{
    subtasks.push_back(Sticky_Task(subtask));
}

int Task::number_of_subtask()
{
    return subtasks.size();
}

int Task::get_priority()
{
    return priority;
}

bool Task::get_persistence()
{
    return persistence;
}

std::string Task::get_name()
{
    return name;
}

void Task::set_persistence(bool persist)
{
    persistence = persist;
}

void Task::run_task(std::chrono::milliseconds frameDuration)
{
    // Ensure thread pool singleton is initialized
    Thread_Pool* threadPool = Thread_Pool::getInstance();

    // Enqueue each subtask to the thread pool for concurrent execution
    for (const auto& subtask : subtasks) {
        // Wrap the subtask in a lambda to capture it by value
        auto taskWrapper = [subtask]() {
            // Execute the subtask
            subtask.task();
            };
        // Enqueue the wrapped task to the thread pool
        threadPool->enqueue(std::move(taskWrapper));
    }
}

void Task::start(std::chrono::milliseconds frameDuration)
{
    run_task(frameDuration);
}

void Task::stop()
{
    auto tasks = subtasks.begin();
    while(tasks != subtasks.end())
    {
        if(tasks->clean_after)
        {
            tasks = subtasks.erase(tasks);
        }
        else
        {
            tasks++;
        }
    }
}

Task& Task::operator=(const Task& other)
{
    if(this != &other)
    {
        name = other.name;
        priority = other.priority;
        percentage = other.percentage;
        persistence = other.persistence;
        is_running = false;
        subtasks = other.subtasks;
        overruns = other.overruns;
    }
    return *this;
}