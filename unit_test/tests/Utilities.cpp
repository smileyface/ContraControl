#include "../test_utilities/system_utilities.h"
#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"

#include "../../dev/Utilities/Utilities/timer.h"


namespace
{
	class Subsystem_Utilities_Test : public ::testing::Test
	{
	protected:
		Timer testing_timer;
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
	while(!testing_timer.timeout(5000));
	ASSERT_GE(testing_timer.get_program_time(), 5) << "Timer alarmed too soon";
	ASSERT_LE(testing_timer.get_program_time(), 5.01) << "Timer alarmed too late";
}
