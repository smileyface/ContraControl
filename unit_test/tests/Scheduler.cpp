#include "../test_utilities/system_utilities.h"
#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"
#include "../../dev/Interfaces/Threading/scheduler/scheduler.h"

namespace
{
    class Scheduler_Test : public ::testing::Test
    {
    protected:
        Scheduler* scheduler;
        virtual void SetUp()
        {
            scheduler = Scheduler::get_instance();
        }
        virtual void TearDown()
        {
            scheduler->destroy_instance();
        }
    };
}


// Test case for the Scheduler class
TEST_F(Scheduler_Test, Add_Task)
{
    Scheduler* scheduler = Scheduler::get_instance();
    Task task("TestTask", 1, 0.5);

    scheduler->add_task(task);

    // Verify that the task was added to the scheduler
    EXPECT_EQ(scheduler->get_number_of_tasks(), 1);
}

TEST_F(Scheduler_Test, Start_The_Scheduler)
{
    Scheduler* scheduler = Scheduler::get_instance();
    Task task1("TestTask", 1, 0.5);

    task1.add_subtask([] ()
                      {
                          std::cout << "Running" << std::endl;
                      });

    scheduler->add_task(task1);
    scheduler->get_number_of_tasks();
    EXPECT_EQ(scheduler->get_number_of_subtasks(), 1);
}

// Test case for running tasks in the scheduler
TEST_F(Scheduler_Test, Run_Tasks)
{
    int subtask1_run_count = 0;
    int subtask2_run_count = 0;
    int subtask3_run_count = 0;

    Scheduler* scheduler = Scheduler::get_instance();
    Task task1("Task1", 1, 0.5);
    Task task2("Task2", 2, 0.3);
    Task task3("Task3", 3, 0.2);

    // Define subtask functions
    auto subtask1 = [&subtask1_run_count] () mutable
    {
        subtask1_run_count++;
    };

    auto subtask2 = [&subtask2_run_count] () mutable
    {
        subtask2_run_count++;
    };

    auto subtask3 = [&subtask3_run_count] () mutable
    {
        subtask3_run_count++;
    };

    // Add subtasks to tasks
    task1.add_subtask(subtask1);
    task1.add_subtask(subtask2);
    task2.add_subtask(subtask1);
    task2.add_subtask(subtask2);
    task3.add_subtask(subtask1);
    task3.add_subtask(subtask3);

    // Add tasks to the scheduler
    scheduler->add_task(task1);
    scheduler->add_task(task2);
    scheduler->add_task(task3);

    // Start the scheduler
    scheduler->start(100); // Frame duration of 100 milliseconds

    // Verify that the tasks were executed
    // ... Add your own assertions here

    system_utilities::sleep_thread(100);
    EXPECT_EQ(subtask1_run_count, 3);
    EXPECT_EQ(subtask2_run_count, 2);
    EXPECT_EQ(subtask3_run_count, 1);
    scheduler->stop();
}