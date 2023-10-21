/*****************************************************************//**
 * \file   task.h
 * \brief  
 * 
 * \author kason
 * \date   March 2023
 *********************************************************************/
#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>
#include <queue>
#include <chrono>
#include <thread>

#include "subtask.h"

 /**
  * @brief The Task class represents a task with subtasks.
  */
class Task
{
public:
    /**
     * @brief Constructs a Task object.
     * @param name The name of the task.
     * @param priority The priority of the task.
     * @param percentage The percentage of frame duration allocated to this task.
     * @param persistence Is the task persistent.
     * @param clear_subtasks Remove all subtasks after the frame.
     */
    Task(const std::string& name, int priority, double percentage, bool persistence, bool clear_subtasks);

    /**
     * @brief Constructs a Task object.
     * @param name The name of the task.
     * @param priority The priority of the task.
     * @param percentage The percentage of frame duration allocated to this task.
     * @param persistence Is the task persistent.
     */
    Task(const std::string& name, int priority, double percentage, bool persistence);

    /**
     * @brief Constructs a Task object.
     * @param name The name of the task.
     * @param priority The priority of the task.
     * @param percentage The percentage of frame duration allocated to this task.
     */
    Task(const std::string& name, int priority, double percentage);

    /**
     * @brief Copy constructor.
     * @param other The Task object to be copied.
     */
    Task(const Task& other);

    /**
     * @brief Default constructor.
     */
    Task();

    /**
     * @brief Default deconstructor
     */
    ~Task();

    /**
     * @brief Adds a subtask to the task.
     * @param subtask The subtask to be added.
     */
    void add_subtask(const Subtask& subtask);

    /**
     * @brief Adds a function to the task as a Sticky_Task.
     * @param subtask The function to be added as a Sticky_Task.
     */
    void add_subtask(const std::function<void()>& subtask);

    /**
     * @brief Get number of subtasks to be run.
     * @returns Number of subtasks.
     */
    int number_of_subtask();

    /**
     * @brief Get number of overruns, defined as a task taking more than 1.5 times over execution time.
     * @returns number of overruns.
     */
    int get_overruns();

    /**
     * @brief Get priority of the task.
     * @returns Priority.
     */
    int get_priority();

    /**
     * @brief Get persistance of task.
     * @returns Persistance
     */
    bool get_persistence();

    /**
     * @brief Get name of the task.
     * @returns Name
     */
    std::string get_name();

    /**
     * @brief Set persistence
     * @param persist Should the task persist
     */
    void set_persistence(bool persist);

    /**
     * @brief Runs the task for the given frame duration.
     * @param frameDuration The duration of a frame.
     */
    void run_task(std::chrono::milliseconds frameDuration);

    /**
     * @brief Starts the execution of the task.
     * @param frame_duration The duration of a frame.
     */
    void start(std::chrono::milliseconds frame_duration);

    /**
     * @brief Stops the execution of the task.
     */
    void stop();

    /**
     * @brief Add an exception thrown in the task.
     * @param ex Exception pointer to exception thrown.
     */
    void exception(std::exception_ptr ex);

    /**
     * @brief Assignment operator override.
     * @param other The Task object to be assigned.
     * @return Reference to the assigned Task object.
     */
    Task& operator=(const Task& other);

private:
    std::string name;
    int priority;
    int overruns;
    bool persistence;
    bool clear_subtasks;
    double percentage;
    bool is_running;
    std::vector<Subtask> subtasks;
    std::vector<std::thread> thread;
    std::queue<std::exception_ptr> thrown_exceptions;
public:
};

#endif // TASK_H