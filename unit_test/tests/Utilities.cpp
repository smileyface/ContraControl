#include "../test_utilities/system_utilities.h"
#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"

#include "../../dev/Utilities/Utilities/timer.h"


namespace
{
	class Subsystem_Utilities_Test : public ::testing::Test
	{
	protected:
		virtual void SetUp()
		{
			system_utilities::setup();
		}
		virtual void TearDown()
		{
			system_utilities::cleanup();
		}
	};
}

TEST_F(Subsystem_Utilities_Test, Timer_Alignment)
{
	Timer::Basic testing;
	double before_clock = std::clock();
	testing.start_clock();
	system_utilities::sleep_thread(1000);
	testing.stop_clock();
	double after_clock = std::clock();
	ASSERT_GE((after_clock - before_clock) / (double) CLOCKS_PER_SEC, 1) << "Timer misalignment";
	ASSERT_LT((after_clock - before_clock) / (double) CLOCKS_PER_SEC, 1.025) << "Timer misalignment";
}

TEST_F(Subsystem_Utilities_Test, Timer_Stop)
{
	Timer::Basic testing;
	double before_clock = std::clock();
	testing.start_clock();
	system_utilities::sleep_thread(1000);
	testing.stop_clock();
	double after_clock = std::clock();
	ASSERT_GE(testing.get_program_time(), 1) << "Timer misalignment";
	ASSERT_LT(testing.get_program_time(), 1.025) << "Timer misalignment";
}

TEST_F(Subsystem_Utilities_Test, Timeout_Timer_Alignment)
{
	Timer::Timeout testing(1000);
	testing.start_clock();
	double before_clock = std::clock();
	testing.join();
	double after_clock = std::clock();
	ASSERT_GE((after_clock - before_clock) / (double) CLOCKS_PER_SEC, 1.0) << "Timer misalignment";
	ASSERT_LT((after_clock - before_clock) / (double) CLOCKS_PER_SEC, 1.025) << "Timer misalignment";
}
TEST_F(Subsystem_Utilities_Test, Timeout_Timer_Timeout)
{
	double before_clock = std::clock();
	Timer::Timeout testing(1000);
	testing.start_clock();
	testing.join();
	ASSERT_TRUE(testing.get_alarm()) << "Alarm did not sound";
	ASSERT_GE(testing.get_program_time(), 1) << "Timer alarmed too soon";
	ASSERT_LE(testing.get_program_time(), 1.025) << "Timer alarmed too late";
}

TEST_F(Subsystem_Utilities_Test, Timeout_Timer_Stop)
{
	Timer::Timeout testing(5000);
	testing.start_clock();
	system_utilities::sleep_thread(1000);
	testing.stop_clock();
	ASSERT_FALSE(testing.get_alarm()) << "Alarm sounded";
	ASSERT_GE(testing.get_program_time(), 1) << "Timer alarmed too soon";
	ASSERT_LE(testing.get_program_time(), 1.025) << "Timer alarmed too late";
}
