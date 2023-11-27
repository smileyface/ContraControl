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
#include <mutex>
#include <condition_variable>
#include <atomic>

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
    void add_task(Task* task);

    /**
     * @brief Adds a system task to the scheduler.
     * The system task is for adding more task to the current frame. It is run as part of PRI_1.
     * 
     * @param task The system task to add to the scheduler.
     */
    void add_system_task(std::function<void()> task);

    /**
     * @brief Adds a cleanup task to the scheduler.
     * The cleanup task is for adding more task to the cleanup frame. It is run as part of PRI_5.
     *
     * @param task The cleanup task to add to the scheduler.
     */
    void add_cleanup_task(std::function<void()> task);

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
     * @brief Gets the number of overruns.
     * @return The number of overrun frames.
     */
    int get_overruns();

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
     * @brief Run a single frame.
     * @param frameDurationMs Duration of the frame.
     */
    void frame(std::chrono::milliseconds frameDurationMs);

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

    std::atomic_bool scheduler_running;
    std::mutex mutex;

    Task system_task;
    Task cleanup_task;

    std::vector<std::vector<Task*>> tasks;
    std::mutex queueMutex;
    std::condition_variable condition;
    int frame_rate;
    std::thread scheduler_thread;
    int overruns;

    static Scheduler* instance;
};

#endif // SCHEDULER_H