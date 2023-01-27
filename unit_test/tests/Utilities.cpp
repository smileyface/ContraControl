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

TEST_F(Subsystem_Utilities_Test, Timer_Timeout)
{
	Timer::Timeout testing(5000);
	testing.join();
	ASSERT_TRUE(testing.get_alarm()) << "Alarm did not sound";
	ASSERT_GE(testing.get_program_time(), 5) << "Timer alarmed too soon";
	ASSERT_LE(testing.get_program_time(), 5.02) << "Timer alarmed too late";
}
