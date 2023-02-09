#include "../../test_utilities/system_utilities.h"
#include "../../test_utilities/test_utilities.h"

#include "../../test_utilities/pch.h"


namespace
{
	class Controller_Subsystem_Test : public ::testing::Test
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



TEST_F(Controller_Subsystem_Test, Controller_Test_Loop)
{
	system_utilities::controller_utilities::start();
	testing_utilities::subsystem_utilities::controller_utilities::check_is_running(true);
	system_utilities::sleep_thread(1000);
	system_utilities::controller_utilities::stop();
	testing_utilities::subsystem_utilities::controller_utilities::check_is_running(false);
}

TEST_F(Controller_Subsystem_Test, Controller_Test_Consumer)
{
	int consumers = Message_Relay::get_instance()->number_of_consumers();
	system_utilities::controller_utilities::start();
	system_utilities::sleep_thread(1000);
	system_utilities::controller_utilities::stop();
	ASSERT_EQ(Message_Relay::get_instance()->number_of_consumers(), consumers) << "Controller consumers not all removed.";
}

TEST_F(Controller_Subsystem_Test, Controller_Test_Memory_Leak)
{
	//TODO: This test <0.0.10

}