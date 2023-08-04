#include "../scheduler/subtask.h"

Subtask Cleaned_Task(std::function<void()> subtask)
{
    return { true,  subtask };
}

Subtask Sticky_Task(std::function<void()> subtask)
{
    return { false, subtask };
}