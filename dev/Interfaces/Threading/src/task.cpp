#include "../scheduler/task.h"

#include <iostream>

Task::Task(const std::string& name, int priority, double percentage)
    : name(name), priority(priority), percentage(percentage), is_running(false)
{ }

Task::Task(const Task& other)
    : name(other.name), priority(other.priority), percentage(other.percentage), is_running(false), subtasks(other.subtasks)
{ 
}


void Task::add_subtask(const std::function<void()>& subtask)
{
    subtasks.push_back(subtask);
}

int Task::number_of_subtask()
{
    return subtasks.size();
}

void Task::run(std::chrono::milliseconds frameDuration)
{
    auto taskExecutionTime = static_cast<int>(frameDuration.count() * percentage);

    auto startTime = std::chrono::steady_clock::now();
    auto currentTime = startTime;
    std::chrono::duration<double> elapsedSeconds = currentTime - startTime;

    for(const auto& subtask : subtasks)
    {
        if(elapsedSeconds >= std::chrono::milliseconds(taskExecutionTime))
        {
            break;
        }
        subtask();

        currentTime = std::chrono::steady_clock::now();
        elapsedSeconds = currentTime - startTime;
    }
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
    if(is_running)
    {
        is_running = false;
        thread.join();
    }
}

bool Task::operator<(const Task& other) const
{
    return priority > other.priority;
}

Task& Task::operator=(const Task& other)
{
    if(this != &other)
    {
        name = other.name;
        priority = other.priority;
        percentage = other.percentage;
        is_running = false;
        subtasks = other.subtasks;
    }
    return *this;
}