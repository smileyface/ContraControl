#include "../scheduler/task.h"

#include <iostream>

int alive_threads = 0;

Task::Task(const std::string& name, int priority, double percentage, bool persistence = false) :
    name(name),
    priority(priority),
    percentage(percentage),
    is_running(false),
    persistence(persistence),
    overruns(0)
{ }

Task::Task(const std::string& name, int priority, double percentage) :
    name(name),
    priority(priority),
    percentage(percentage),
    is_running(false),
    persistence(true),
    overruns(0)
{ }

Task::Task(const Task& other) :
    name(other.name), 
    priority(other.priority), 
    percentage(other.percentage), 
    is_running(false), 
    persistence(other.persistence),
    subtasks(other.subtasks),
    overruns(other.overruns)
{ }

Task::~Task()
{
    stop();
}

void Task::add_subtask(const std::function<void()>& subtask)
{
    subtasks.push_back(subtask);
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

void Task::run(std::chrono::milliseconds frameDuration)
{
    alive_threads++;

    for(const auto& subtask : subtasks)
    {
        subtask();
    }
    is_running = false;
    alive_threads--;
}

void Task::start(std::chrono::milliseconds frameDuration)
{
    if(!is_running)
    {
        is_running = true;
        thread = std::thread(&Task::run, this, frameDuration);
    }
}

void Task::stop()
{
    if(thread.joinable())
    {
        thread.join();
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
    }
    return *this;
}