#include "../test_utilities/device_utilities.h"
#include "../test_utilities/system_utilities.h"
#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"


namespace {
	class Device_Switch_Test : public ::testing::Test {
	protected:
		Device_Label dl;
		virtual void SetUp() {
			system_utilities::setup();
			system_utilities::start_system();
			device_utilities::start_test_environment();
			dl = device_utilities::add_device(Device_Creator((int)DEVICE_IDENTIFIER::SWITCH, "Test1"));
		}
		virtual void TearDown() {
			system_utilities::stop_system();
			system_utilities::cleanup();
		}
	};
	class Device_Gradient_Test : public ::testing::Test {
	protected:
		Device_Label dl;
		virtual void SetUp() {
			system_utilities::setup();
			system_utilities::start_system();
			device_utilities::start_test_environment();
			dl = device_utilities::add_device(Device_Creator((int)DEVICE_IDENTIFIER::GRADIENT, "Test1"));
		}
		virtual void TearDown() {
			system_utilities::stop_system();
			system_utilities::cleanup();
		}
	};
	class Device_RGB_Test : public ::testing::Test {
	protected:
		Device_Label dl;
		virtual void SetUp() {
			system_utilities::setup();
			system_utilities::start_system();
			device_utilities::start_test_environment();
			dl = device_utilities::add_device(Device_Creator((int)DEVICE_IDENTIFIER::RGB, "Test1"));
		}
		virtual void TearDown() {
			system_utilities::stop_system();
			system_utilities::cleanup();
		}
	};
	class Device_Invalid_Test : public ::testing::Test {
	protected:
		Device_Label dl;
		virtual void SetUp() {
			device_utilities::start_test_environment();
			system_utilities::start_system();
			dl = device_utilities::add_device(Device_Creator((int)DEVICE_IDENTIFIER::INVALID, "Test1"));
		}
		virtual void TearDown() {
			system_utilities::stop_system();
			system_utilities::cleanup();
		}
	};
}

//========================================
//
//        Switch Testing Block
//
//========================================
TEST_F(Device_Switch_Test, Device_Created) {
	testing_utilities::device_utilities::check_type(dl, DEVICE_IDENTIFIER::SWITCH);
}
TEST_F(Device_Switch_Test, Device_Invalid) {
	testing_utilities::device_utilities::check_validity(dl, false);
	device_utilities::command_device(dl, new Initalize("Test1"));
	testing_utilities::device_utilities::check_validity(dl, true);
}
TEST_F(Device_Switch_Test, Device_Removed) {
	testing_utilities::device_utilities::check_type(dl, DEVICE_IDENTIFIER::SWITCH);
	device_utilities::remove_device(dl);
	EXPECT_THROW(testing_utilities::device_utilities::check_type(dl, DEVICE_IDENTIFIER::SWITCH), DeviceNotFoundException);
}
TEST_F(Device_Switch_Test, Device_Naming) {
	device_utilities::command_device(dl, new Initalize("Test1"));
	testing_utilities::device_utilities::check_name(dl, DEVICE_IDENTIFIER::SWITCH, "Test1");
}

TEST_F(Device_Gradient_Test, Device_Created) {
	testing_utilities::device_utilities::check_type(dl, DEVICE_IDENTIFIER::GRADIENT);
}
TEST_F(Device_Gradient_Test, Device_Invalid) {
	testing_utilities::device_utilities::check_validity(dl, false);
	device_utilities::command_device(dl, new Initalize("Test1"));
	testing_utilities::device_utilities::check_validity(dl, true);
}
TEST_F(Device_Gradient_Test, Device_Removed) {
	testing_utilities::device_utilities::check_type(dl, DEVICE_IDENTIFIER::GRADIENT);
	device_utilities::remove_device(dl);
	EXPECT_THROW(testing_utilities::device_utilities::check_type(dl, DEVICE_IDENTIFIER::GRADIENT), DeviceNotFoundException);
}
TEST_F(Device_Gradient_Test, Device_Naming) {
	device_utilities::command_device(dl, new Initalize("Test1"));
	testing_utilities::device_utilities::check_name(dl, DEVICE_IDENTIFIER::GRADIENT, "Test1");
}

TEST_F(Device_RGB_Test, Device_Created) {
	testing_utilities::device_utilities::check_type(dl, DEVICE_IDENTIFIER::RGB);
}
TEST_F(Device_RGB_Test, Device_Invalid) {
	testing_utilities::device_utilities::check_validity(dl, false);
	device_utilities::command_device(dl, new Initalize("Test1"));
	testing_utilities::device_utilities::check_validity(dl, true);
}
TEST_F(Device_RGB_Test, Device_Removed) {
	testing_utilities::device_utilities::check_type(dl, DEVICE_IDENTIFIER::RGB);
	device_utilities::remove_device(dl);
	EXPECT_THROW(testing_utilities::device_utilities::check_type(dl, DEVICE_IDENTIFIER::RGB), DeviceNotFoundException);
}
TEST_F(Device_RGB_Test, Device_Naming) {
	device_utilities::command_device(dl, new Initalize("Test1"));
	testing_utilities::device_utilities::check_name(dl, DEVICE_IDENTIFIER::RGB, "Test1");
}

TEST_F(Device_Invalid_Test, Device_Invalid) {
	testing_utilities::device_utilities::check_validity(dl, false);
}

TEST_F(Device_Invalid_Test, Device_Naming) {
	device_utilities::command_device(dl, new Initalize("Test1"));
	testing_utilities::device_utilities::check_name(dl, DEVICE_IDENTIFIER::INVALID, "Test1");
}