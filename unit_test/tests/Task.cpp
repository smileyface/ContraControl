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
TEST_F(Task_Test, Double_Start_Subtask)
{
	Task task("TestTask", 1, 0.5);
	int counter = 0;

	// Define subtask function
	auto subtask = [&counter] ()
	{
		counter++;
	};

	task.add_subtask(subtask);

	task.start(std::chrono::milliseconds(500));
	EXPECT_NO_THROW(task.start(std::chrono::milliseconds(500)));

	task.stop();
}

// Test case for the Task class
TEST_F(Task_Test, Double_Stop_Subtask)
{
	Task task("TestTask", 1, 0.5);
	int counter = 0;

	// Define subtask function
	auto subtask = [&counter] ()
	{
		counter++;
	};

	task.add_subtask(subtask);

	task.start(std::chrono::milliseconds(500));

	task.stop();
	EXPECT_NO_THROW(task.stop());
}

TEST_F(Task_Test, Assignment)
{
	Task task("Task", 1, 0.5);
	Task* task_2 = &task;
	task = task;
	EXPECT_EQ(&task, task_2);

	Task task_3("Task3", 2, 0.5);
	task = task_3;
	EXPECT_EQ(task.get_name(), task_3.get_name());
	EXPECT_NE(&task, &task_3);
}
