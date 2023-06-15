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
#include <functional>
#include <vector>
#include <chrono>
#include <thread>

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
     * @brief Adds a subtask to the task.
     * @param subtask The subtask to be added.
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
     * @brief Runs the task for the given frame duration.
     * @param frameDuration The duration of a frame.
     */
    void run(std::chrono::milliseconds frameDuration);

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
     * @brief Overloaded less-than operator to compare tasks based on priority.
     * @param other The other Task object to compare with.
     * @return True if this task has lower priority than the other task, false otherwise.
     */
    bool operator<(const Task& other) const;

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
    double percentage;
    std::vector<std::function<void()>> subtasks;
    bool is_running;
    std::thread thread;
public:
};

#endif // TASK_H