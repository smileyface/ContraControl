#include "../test_utilities/system_utilities.h"
#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"


namespace {
	class Subsystem_Test : public ::testing::Test {
	protected:
		virtual void SetUp() {
			system_utilities::setup();
		}
		virtual void TearDown() {
			system_utilities::cleanup();
		}
	};
}

TEST_F(Subsystem_Test, Model_Test_Loop)
{
	system_utilities::model_utilities::start();
	testing_utilities::subsystem_utilities::model_utilities::check_is_running(true);
	system_utilities::sleep_thread(1000);
	system_utilities::model_utilities::stop();
	testing_utilities::subsystem_utilities::model_utilities::check_is_running(false);
}

TEST_F(Subsystem_Test, Controller_Test_Loop)
{
	system_utilities::controller_utilities::start();
	testing_utilities::subsystem_utilities::controller_utilities::check_is_running(true);
	system_utilities::sleep_thread(1000);
	system_utilities::controller_utilities::stop();
	testing_utilities::subsystem_utilities::controller_utilities::check_is_running(false);
}

TEST_F(Subsystem_Test, Commander_Destroy_With_Not_Run_Commands)
{
	system_utilities::setup();
	system_utilities::start_system();

	controller::add_command(Packed_Command(Commander::get_instance()->make_command<Device_Create>("Test_Node", 0, "Test_Device"), 0));

	EXPECT_EQ(Commander::get_instance()->get_number_of_commands(), 1);
	Commander::destroy_instance();
	EXPECT_EQ(Commander::get_instance()->get_number_of_commands(), 0);
}
