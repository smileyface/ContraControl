#include "../test_utilities/system_utilities.h"
#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"
#include "../../dev/Interfaces/Threading/thread_pool.h"

namespace
{
	class Threading_Test : public ::testing::Test
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

TEST_F(Threading_Test, Add_Threads)
{
	EXPECT_EQ(Thread_Pool::get_instance()->number_of_threads(), 0);
	Thread_Pool::get_instance()->update_thread_count(2);
	EXPECT_EQ(Thread_Pool::get_instance()->number_of_threads(), 2);
}

TEST_F(Threading_Test, Remove_Threads)
{
	Thread_Pool::get_instance()->update_thread_count(2);
	EXPECT_EQ(Thread_Pool::get_instance()->number_of_threads(), 2);
	Thread_Pool::get_instance()->update_thread_count(1);
	EXPECT_EQ(Thread_Pool::get_instance()->number_of_threads(), 1);
	Thread_Pool::get_instance()->update_thread_count(0);
}

TEST_F(Threading_Test, Add_Remove_Threads)
{
	EXPECT_EQ(Thread_Pool::get_instance()->number_of_threads(), 0);
	EXPECT_EQ(Thread_Pool::get_instance()->running(), false);
	Thread_Pool::get_instance()->update_thread_count(2);
	EXPECT_EQ(Thread_Pool::get_instance()->number_of_threads(), 2);
	EXPECT_EQ(Thread_Pool::get_instance()->running(), true);
	Thread_Pool::get_instance()->update_thread_count(1);
	EXPECT_EQ(Thread_Pool::get_instance()->number_of_threads(), 1);
	EXPECT_EQ(Thread_Pool::get_instance()->running(), true);
	Thread_Pool::get_instance()->update_thread_count(4);
	EXPECT_EQ(Thread_Pool::get_instance()->number_of_threads(), 4);
	EXPECT_EQ(Thread_Pool::get_instance()->running(), true);	
	Thread_Pool::get_instance()->update_thread_count(0);
	EXPECT_EQ(Thread_Pool::get_instance()->number_of_threads(), 0);
	EXPECT_EQ(Thread_Pool::get_instance()->running(), false);
}

TEST_F(Threading_Test, Add_Job_To_Queue)
{
	bool function_run = false;
	Thread_Pool::get_instance()->update_thread_count(1);
	Thread_Pool::get_instance()->add_job([&function_run] ()
										 {
											 function_run = true;
										 });
	system_utilities::sleep_thread(1);
	EXPECT_TRUE(function_run);
	Thread_Pool::get_instance()->update_thread_count(0);
}
