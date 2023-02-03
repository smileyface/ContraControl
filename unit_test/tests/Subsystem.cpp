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

TEST_F(Subsystem_Test, Model_Test_Consumer)
{
	//Currently no consumer
}

TEST_F(Subsystem_Test, Model_Test_Memory_Leak)
{
	//TODO: This test <0.0.10

}

TEST_F(Subsystem_Test, Controller_Test_Loop)
{
	system_utilities::controller_utilities::start();
	testing_utilities::subsystem_utilities::controller_utilities::check_is_running(true);
	system_utilities::sleep_thread(1000);
	system_utilities::controller_utilities::stop();
	testing_utilities::subsystem_utilities::controller_utilities::check_is_running(false);
}

TEST_F(Subsystem_Test, Controller_Test_Consumer)
{
	//Currently no consumer
}

TEST_F(Subsystem_Test, View_Test_Loop)
{
	system_utilities::view_utilities::start();
	testing_utilities::subsystem_utilities::view_utilities::check_is_running(true);
	system_utilities::sleep_thread(1000);
	system_utilities::view_utilities::stop();
	testing_utilities::subsystem_utilities::controller_utilities::check_is_running(false);
}