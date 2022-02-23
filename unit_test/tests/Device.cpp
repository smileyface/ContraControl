#include "../test_utilities/device_utilities.h"
#include "../test_utilities/system_testings.h"
#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"


namespace {
	class Device_Switch_Test : public ::testing::Test {
	protected:
		Device_Label dl;
		virtual void SetUp() {
			device_utilities::start_test_environment();
			dl = device_utilities::add_device(Device_Creator((int)DEVICE_IDENTIFIER::SWITCH, "Test1"));
		}
		virtual void TearDown() {
			system_util::cleanup();
		}

	};
	class Device_Gradient_Test : public ::testing::Test {
	protected:
		Device_Label dl;
		virtual void SetUp() {
			device_utilities::start_test_environment();
			dl = device_utilities::add_device(Device_Creator((int)DEVICE_IDENTIFIER::GRADIENT, "Test1"));
		}
		virtual void TearDown() {
			system_util::cleanup();
		}
	};
	class Device_Invalid_Test : public ::testing::Test {
	protected:
		Device_Label dl;
		virtual void SetUp() {
			device_utilities::start_test_environment();
			dl = device_utilities::add_device(Device_Creator((int)DEVICE_IDENTIFIER::INVALID, "Test1"));
		}
		virtual void TearDown() {
			system_util::cleanup();
		}
	};
}

//========================================
//
//        Switch Testing Block
//
//========================================
TEST_F(Device_Switch_Test, Device_Created) {
	testing_util::device_utilities::check_type(dl, DEVICE_IDENTIFIER::SWITCH);
}
TEST_F(Device_Switch_Test, Device_Invalid) {
	testing_util::device_utilities::check_validity(dl, false);
	device_utilities::command_device(dl, new Initalize("Test1"));
	testing_util::device_utilities::check_validity(dl, true);
}

TEST_F(Device_Gradient_Test, Device_Created) {
	testing_util::device_utilities::check_type(dl, DEVICE_IDENTIFIER::GRADIENT);
}
TEST_F(Device_Gradient_Test, Device_Invalid) {
	testing_util::device_utilities::check_validity(dl, false);
	device_utilities::command_device(dl, new Initalize("Test1"));
	testing_util::device_utilities::check_validity(dl, true);
}

TEST_F(Device_Invalid_Test, Device_Invalid) {
	testing_util::device_utilities::check_validity(dl, false);
}