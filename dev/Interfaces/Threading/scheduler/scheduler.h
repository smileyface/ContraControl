/*****************************************************************//**
 * \file   scheduler.h
 * \brief  
 * 
 * \author kason
 * \date   April 2023
 *********************************************************************/
#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "task.h"
#include <queue>
#include <mutex>

/**
 * @brief The Scheduler class manages the scheduling and execution of tasks.
 */
class Scheduler {
public:
    /**
     * @brief Gets the singleton instance of the Scheduler.
     * @return The Scheduler instance.
     */
    static Scheduler* get_instance();

    /**
     * @brief Destroys the instance of the Scheduler
     */
    static void destroy_instance();

    /**
     * @brief Adds a task to the scheduler.
     * @param task The task to be added.
     */
    void add_task(Task task);

    /**
     * @brief Gets number of tasks on the scheduler.
     * @return The number of tasks.
     */
    int get_number_of_tasks();

    /**
     * @brief Gets the total number of subtasks in each task on the scheduler.
     * @return The number of subtasks.
     */
    int get_number_of_subtasks();

    /**
     * @brief Starts the execution of the tasks with the given frame duration.
     * @param frame_rate The duration of a frame.
     */
    void start(int frame_rate);

    /**
     * @brief Stops the execution of all tasks.
     */
    void stop();

    /**
     * @brief Remove all tasks from the scheduler.
     */
    void clear();

private:
    Scheduler();
    ~Scheduler();
    Scheduler(const Scheduler&) = delete;
    Scheduler& operator=(const Scheduler&) = delete;
    void clean_persistence();
    void frame_run();

    bool scheduler_running;

    std::vector<std::vector<Task>> tasks;
    int frame_rate;
    std::thread scheduler_thread;

    static Scheduler* instance;
};

#endif // SCHEDULER_H