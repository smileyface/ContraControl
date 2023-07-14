#include "../test_utilities/system_utilities.h"
#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"
#include "../../dev/Interfaces/Threading/scheduler/scheduler.h"

#include <algorithm>

namespace
{
    class Scheduler_Test : public ::testing::Test
    {
    protected:
        Scheduler* scheduler;
        virtual void SetUp()
        {
            system_utilities::setup_messaging();
            scheduler = Scheduler::get_instance();
        }
        virtual void TearDown()
        {
            scheduler->destroy_instance();
            system_utilities::cleanup();
        }
    };
}


// Test case for the Scheduler class
TEST_F(Scheduler_Test, Add_Task)
{
    Task task("TestTask", 1, 0.5);

    scheduler->add_task(&task);

    // Verify that the task was added to the scheduler
    EXPECT_EQ(scheduler->get_number_of_tasks(), 3);
}



TEST_F(Scheduler_Test, Start_The_Scheduler)
{
    Task task1("TestTask", 1, 0.5);

    task1.add_subtask([] ()
                      {
                          std::cout << "Running" << std::endl;
                      });

    scheduler->add_task(&task1);
    scheduler->get_number_of_tasks();
    EXPECT_EQ(scheduler->get_number_of_subtasks(), 1);
}

// Test case for running tasks in the scheduler
TEST_F(Scheduler_Test, Run_Tasks)
{
    int subtask1_run_count = 0;
    int subtask2_run_count = 0;
    int subtask3_run_count = 0;

    Task task1("Task1", 1, 0.5, false);
    Task task2("Task2", 2, 0.3, false);
    Task task3("Task3", 3, 0.2, false);

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
    scheduler->add_task(&task1);
    scheduler->add_task(&task2);
    scheduler->add_task(&task3);

    // Start the scheduler
    scheduler->start(100); 

    // Verify that the tasks were executed
    // ... Add your own assertions here

    system_utilities::sleep_thread(100);
    scheduler->stop();
    EXPECT_EQ(subtask1_run_count, 3);
    EXPECT_EQ(subtask2_run_count, 2);
    EXPECT_EQ(subtask3_run_count, 1);
}

TEST_F(Scheduler_Test, Run_Tasks_In_Order)
{
    std::vector<int> called_order;

    Task task1("Task1", 1, 0.2, false);
    Task task2("Task2", 3, 0.2, false);
    Task task3("Task3", 2, 0.2, false);

    // Define subtask functions
    auto subtask1 = [&called_order] () mutable
    {
        called_order.push_back(1);
    };

    auto subtask2 = [&called_order] () mutable
    {
        called_order.push_back(2);
    };

    auto subtask3 = [&called_order] () mutable
    {
        called_order.push_back(3);
    };

    // Add subtasks to tasks
    task1.add_subtask(subtask1);
    task2.add_subtask(subtask2);
    task3.add_subtask(subtask3);

    // Add tasks to the scheduler
    scheduler->add_task(&task1);
    scheduler->add_task(&task2);
    scheduler->add_task(&task3);

    // Start the scheduler
    scheduler->start(100); // Frame duration of 100 milliseconds

    // Verify that the tasks were executed
    // ... Add your own assertions here

    system_utilities::sleep_thread(100);
    scheduler->stop();

    if(called_order.size() != 3)
    {
        ADD_FAILURE() << "Subtasks not called";
    }
    else
    {
        EXPECT_EQ(called_order[0], 1);
        EXPECT_EQ(called_order[1], 3);
        EXPECT_EQ(called_order[2], 2);
    }
}

TEST_F(Scheduler_Test, Priority_Out_Of_Bounds)
{
    Task task1("Task1", 11, 0.5);
    Task task2("Task1", 0, 0.5);
    Task task_valid_1("Valid Task", 1, 0.5);
    Task task_valid_2("Valid Task", 10, 0.5);
    scheduler->add_task(&task1);
    EXPECT_EQ(scheduler->get_number_of_tasks(), 2);
    scheduler->add_task(&task2);
    EXPECT_EQ(scheduler->get_number_of_tasks(), 2);
    scheduler->add_task(&task_valid_1);
    EXPECT_EQ(scheduler->get_number_of_tasks(), 3);
    scheduler->add_task(&task_valid_2);
    EXPECT_EQ(scheduler->get_number_of_tasks(), 4);

}

TEST_F(Scheduler_Test, Scheduler_Singleton_Instantiations)
{
    EXPECT_EQ(scheduler, Scheduler::get_instance());
}

TEST_F(Scheduler_Test, Scheduler_Destroy)
{
    Scheduler::destroy_instance();
    EXPECT_NO_THROW(Scheduler::destroy_instance());
}

TEST_F(Scheduler_Test, Cancel_The_Scheduler)
{
    std::vector<int> called_order;

    Task task1("Task1", 1, 0.5);
    Task task2("Task2", 3, 0.3);
    Task task3("Task3", 2, 0.2);

    // Define subtask functions
    auto subtask1 = [&called_order] () mutable
    {
        called_order.push_back(1);
    };

    auto subtask2 = [&called_order] () mutable
    {
        called_order.push_back(2);
    };

    auto subtask3 = [&called_order] () mutable
    {
        called_order.push_back(3);
    };

    // Add subtasks to tasks
    task1.add_subtask(subtask1);
    task2.add_subtask(subtask2);
    task3.add_subtask(subtask3);

    // Add tasks to the scheduler
    scheduler->add_task(&task1);
    scheduler->add_task(&task2);
    scheduler->add_task(&task3);

    EXPECT_EQ(scheduler->get_number_of_tasks(), 5);

    scheduler->stop();
    scheduler->clear();

    EXPECT_EQ(called_order.size(), 0);
    EXPECT_EQ(scheduler->get_number_of_tasks(), 0);
}

TEST_F(Scheduler_Test, Test_Persistence)
{
    Task test_task("Test", 2, .3, false);
    test_task.add_subtask([] ()
                          {

                          });
    scheduler->add_task(&test_task);
    EXPECT_EQ(scheduler->get_number_of_tasks(), 3);
    scheduler->start(10);
    system_utilities::sleep_thread(200);
    scheduler->stop();
    EXPECT_EQ(scheduler->get_number_of_tasks(), 2);

    int run_count = 0;
    Task test_task_2("Test2", 2, .3, true);
    test_task_2.add_subtask([&run_count] ()
                          {
                              run_count++;
                          });
    scheduler->add_task(&test_task_2);
    EXPECT_EQ(scheduler->get_number_of_tasks(), 3);
    scheduler->start(10);
    system_utilities::sleep_thread(200);
    scheduler->stop();
    EXPECT_EQ(scheduler->get_number_of_tasks(), 3);
}

TEST_F(Scheduler_Test, Test_Scheduler_Looping)
{
    int run_count = 0;
    Task test_task("Test", 2, 0.3);
    test_task.add_subtask([&run_count] () mutable
                          {
                              run_count++;
                          });
    scheduler->add_task(&test_task);
    scheduler->start(27);
    system_utilities::sleep_thread(100);
    scheduler->stop();
    EXPECT_EQ(run_count, 3);
}

TEST_F(Scheduler_Test, Test_Scheduler_Overrun)
{
    Task test_task("Test", 1, 0.3, false);
    test_task.add_subtask(Cleaned_Task([] () mutable
                          {
                              system_utilities::sleep_thread(100);
                          }));
    scheduler->add_task(&test_task);
    scheduler->start(30);
    system_utilities::sleep_thread(1000);
    scheduler->stop();
    EXPECT_EQ(scheduler->get_overruns(), 1);
}

TEST_F(Scheduler_Test, Add_Task_With_Scheduler_Running)
{
    bool run = false;
    Task test_task("Test", 1, 0.3, false);

    scheduler->add_task(&test_task);
    scheduler->start(30);
    test_task.add_subtask([&run] () mutable
                          {
                              run = true;
                          });
    system_utilities::sleep_thread(1000);
    scheduler->stop();
    EXPECT_TRUE(run);
}

TEST_F(Scheduler_Test, System_Task)
{
    int run_id = 0;
    scheduler->add_system_task([&run_id] () mutable
                               {
                                   run_id = 42;
                               });
    scheduler->start(30);
    system_utilities::sleep_thread(1000);
    scheduler->stop();
    EXPECT_EQ(run_id, 42);
}

TEST_F(Scheduler_Test, Cleanup_Task)
{
    int run_id = 0;
    scheduler->start(30);
    scheduler->add_cleanup_task([&run_id] () mutable
                               {
                                   run_id = 42;
                               });
    system_utilities::sleep_thread(1000);
    scheduler->stop();
    EXPECT_EQ(run_id, 42);
}

TEST_F(Scheduler_Test, Dryrun_The_System_and_Cleanups)
{
    std::vector<int> runs;

    Task test_task("Test", 2, 0.3, false);
    scheduler->add_task(&test_task);
    scheduler->add_system_task([&runs, test_task] () mutable
                               {
                                   runs.push_back(0);
                                   test_task.add_subtask([&runs] () mutable
                                                         {
                                                             runs.push_back(1);
                                                         });
                               });
    scheduler->add_cleanup_task([&runs] () mutable
                                {
                                    runs.push_back(2);
                                });

    scheduler->start(30);
    system_utilities::sleep_thread(100);
    scheduler->stop();
    auto begin_run = std::find(runs.begin(), runs.end(), 0);
    auto cleanup_run = std::find(runs.begin(), runs.end(), 2);
    EXPECT_NE(begin_run, runs.end());
    EXPECT_NE(cleanup_run, runs.end());
}
