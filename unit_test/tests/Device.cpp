#include "../test_utilities/device_utilities.h"
#include "../test_utilities/system_testings.h"
#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"


namespace {
	class Device_Switch_Test : public ::testing::Test {
	protected:
		Device_Label dl;
		virtual void SetUp() {
			system_util::setup();
			device_utilities::setup_node("Test_Node_Local");
			dl = device_utilities::add_device("Test_Node_Local", Device_Creator((int)DEVICE_IDENTIFIER::SWITCH, "Test1"));
		}
		virtual void TearDown() {
			system_util::cleanup();
		}
	};
	class Device_Gradient_Test : public ::testing::Test {
	protected:
		Device_Label dl;
		virtual void SetUp() {
			system_util::setup();
			device_utilities::setup_node("Test_Node_Local");
			dl = device_utilities::add_device("Test_Node_Local", Device_Creator((int)DEVICE_IDENTIFIER::SWITCH, "Test1"));
		}
		virtual void TearDown() {
			system_util::cleanup();
		}
	};
}


TEST_F(Device_Switch_Test, Device_Invalid) {
	device_utilities::command_device(dl, new On());
	testing_util::device_utilities::check_validity(dl, false);
	device_utilities::initalize_device(dl);
	testing_util::device_utilities::check_validity(dl, true);
}

TEST_F(Device_Gradient_Test, Device_Invalid) {
	device_utilities::command_device(dl, new On());
	testing_util::device_utilities::check_validity(dl, false);
	device_utilities::initalize_device(dl);
	testing_util::device_utilities::check_validity(dl, true);
}