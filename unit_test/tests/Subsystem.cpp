#include "../test_utilities/system_utilities.h"
#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"


namespace {
	class Subsystem_Test : public ::testing::Test {
	protected:
		virtual void SetUp() {
			model::initalize();
		}
		virtual void TearDown() {
			model::clean_up();
		}
	};
}

TEST_F(Subsystem_Test, Model_Test_Loop)
{
	system_utilities::model_utilities::start();
	testing_utilities::subsystem_utilities::model_utilities::check_is_running(true);
	system_utilities::sleep_thread(1);
	system_utilities::model_utilities::stop();
	testing_utilities::subsystem_utilities::model_utilities::check_is_running(false);
}

TEST_F(Subsystem_Test, Controller_Test_Loop)
{
	system_utilities::controller_utilities::start();
	testing_utilities::subsystem_utilities::controller_utilities::check_is_running(true);
	system_utilities::sleep_thread(1);
	system_utilities::controller_utilities::stop();
	testing_utilities::subsystem_utilities::controller_utilities::check_is_running(false);
}
