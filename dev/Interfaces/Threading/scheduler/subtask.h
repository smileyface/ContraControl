/*****************************************************************//**
 * \file   subtask.h
 * \brief  
 * 
 * \author kason
 * \date   July 2023
 *********************************************************************/


#include <functional>

 /**
  * @brief A subtask to be run during the runtime of the Task.
  */
struct Subtask
{
    bool clean_after; ///<Remove this subtask from the run list after run
    std::function<void()> task; ///<Task to run
};

/**
 * @brief A subtask that is removed from the run list after it is run. A run-once task.
 * @param subtask A subtask to run as a one off
 * @return A created one off sub task.
 */
Subtask Cleaned_Task(std::function<void()> subtask);

/**
 * @brief A subtask that sticks around the run list after it is run.
 * @param subtask A subtask to run everytime the task is run.
 * @return A created sub task that will run everytime the parent task is run.
 */
Subtask Sticky_Task(std::function<void()> subtask);