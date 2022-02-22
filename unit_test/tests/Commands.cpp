#include "../test_utilities/device_utilities.h"
#include "../test_utilities/system_testings.h"
#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"


namespace {
	class Device_Commands_Test : public ::testing::Test {
	protected:
		Device_Label dl;
		virtual void SetUp() {
			device_utilities::start_test_environment();
			dl = device_utilities::add_device(Device_Creator((int)DEVICE_IDENTIFIER::SWITCH, "Test1"));
			device_utilities::initalize_device(dl);
		}
		virtual void TearDown() {
			system_util::cleanup();
		}
		void switch_to_device(DEVICE_IDENTIFIER device_type) {
			device_utilities::remove_device(dl);
			dl = device_utilities::add_device(Device_Creator((int)device_type, "Test1"));
		}
	};

	class Device_Commands_Test_No_Init : public ::testing::Test {
	protected:
		Device_Label dl;
		virtual void SetUp() {
			device_utilities::start_test_environment();
			dl = device_utilities::add_device( Device_Creator((int)DEVICE_IDENTIFIER::SWITCH, "Test1"));
		}
		virtual void TearDown() {
			system_util::cleanup();
		}

	};
}

TEST_F(Device_Commands_Test, Device_Initalize) {
	Device* ds = create_device_instance(Device_Creator((int)DEVICE_IDENTIFIER::SWITCH, "Results"));
	ds->initalize("Test1");
	testing_util::device_utilities::check_state(dl, ds);
}

TEST_F(Device_Commands_Test, Device_On) {
	Device* ds = static_cast<Device*>(device_utilities::command_device(dl, new On()));
	testing_util::device_utilities::check_state(dl, ds);
}

TEST_F(Device_Commands_Test, Device_Off) {
	Device* ds = static_cast<Device*>(device_utilities::command_device(dl, new On()));
	testing_util::device_utilities::check_state(dl, ds);

	ds = static_cast<Device*>(device_utilities::command_device(dl, new Off()));
	testing_util::device_utilities::check_state(dl, ds);
}

TEST_F(Device_Commands_Test_No_Init, Device_On) {
	Device* ds = static_cast<Device*>(device_utilities::command_device_no_init(dl, new On()));
	testing_util::device_utilities::check_state(dl, ds);
}

TEST_F(Device_Commands_Test_No_Init, Device_Off) {
	Device* ds = static_cast<Device*>(device_utilities::command_device_no_init(dl, new On()));
	testing_util::device_utilities::check_state(dl, ds);

	ds = static_cast<Device*>(device_utilities::command_device_no_init(dl, new Off()));
	testing_util::device_utilities::check_state(dl, ds);
}

