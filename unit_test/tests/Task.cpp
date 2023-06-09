#include "../test_utilities/system_utilities.h"
#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"
#include "../../dev/Interfaces/Threading/scheduler/scheduler.h"

namespace
{
	class Task_Test : public ::testing::Test
	{
	protected:
		virtual void SetUp()
		{

		}
		virtual void TearDown()
		{

		}
	};
}

// Test case for the Task class
TEST_F(Task_Test, AddSubtask)
{
	Task task("TestTask", 1, 0.5);
	int counter = 0;

	// Define subtask function
	auto subtask = [&counter] ()
	{
		counter++;
	};

	task.add_subtask(subtask);

	// Verify that the subtask was added
	EXPECT_EQ(task.number_of_subtask(), 1);
}

// Test case for the Task class
TEST_F(Task_Test, Subtask_Overrun)
{
	Task task("OverrunTask", 1, 0.5);
	Task task_2("Non Overrunning Task", 1, 0.5);
	int counter = 0;

	// Define subtask function
	auto subtask = [&counter] ()
	{
		system_utilities::sleep_thread(1000);
	};
	auto subtask2 = [&counter] ()
	{
		system_utilities::sleep_thread(600);
	};

	task.add_subtask(subtask);
	task.add_subtask(subtask2);
	task.start(std::chrono::milliseconds(500));


	task.stop();

	// Verify that the subtask was added
	EXPECT_EQ(task.get_overruns(), 1);

	task_2.add_subtask(subtask2);
	task_2.add_subtask(subtask);
	task_2.start(std::chrono::milliseconds(1000));

	task_2.stop();

	EXPECT_EQ(task_2.get_overruns(), 0);
}