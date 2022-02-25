#include "../test_utilities/system_testings.h"
#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"


namespace {
	class Subsystem_Test : public ::testing::Test {
	protected:
		Device_Label dl;
		virtual void SetUp() {
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
	system_utilities::model_utilities::stop();
	testing_utilities::subsystem_utilities::model_utilities::check_is_running(false);
}
