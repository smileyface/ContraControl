#include "../test_utilities/device_utilities.h"
#include "../test_utilities/system_testings.h"
#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"


namespace {
	class Commands_Test : public ::testing::Test {
	protected:
		Device_Label dl;
		virtual void SetUp() {
			device_utilities::start_test_environment();
			dl = device_utilities::add_device(Device_Creator((int)DEVICE_IDENTIFIER::SWITCH, "Test1"));
		}
		virtual void TearDown() {
			system_util::cleanup();
		}
		void switch_to_device(DEVICE_IDENTIFIER device_type) {
			device_utilities::remove_device(dl);
			dl = device_utilities::add_device(Device_Creator((int)device_type, "Test1"));
		}
	};
}

TEST_F(Commands_Test, Device_Initalize) {

	Device* ds = create_device_instance(Device_Creator((int)DEVICE_IDENTIFIER::SWITCH, "Results"));
	testing_util::device_utilities::check_state(dl, ds);
	ds = static_cast<Device*>(device_utilities::command_device(dl, new Initalize("Test1")));
	testing_util::device_utilities::check_state(dl, ds);
}
TEST_F(Commands_Test, Device_On) {
	Device* ds = static_cast<Device*>(device_utilities::command_device(dl, new On()));
	testing_util::device_utilities::check_state(dl, ds);
	ds = static_cast<Device*>(device_utilities::command_device(dl, new Initalize("Test1")));
	ds = static_cast<Device*>(device_utilities::command_device(dl, new On()));
	testing_util::device_utilities::check_state(dl, ds);
}

TEST_F(Commands_Test, Device_Off) {
	Device * ds = static_cast<Device*>(device_utilities::command_device(dl, new Off()));
	testing_util::device_utilities::check_state(dl, ds);
	ds = static_cast<Device*>(device_utilities::command_device(dl, new Initalize("Test1")));
	ds = static_cast<Device*>(device_utilities::command_device(dl, new On()));
	testing_util::device_utilities::check_state(dl, ds);

	ds = static_cast<Device*>(device_utilities::command_device(dl, new Off()));
	testing_util::device_utilities::check_state(dl, ds);
}

TEST_F(Commands_Test, Device_Assign_Channel) {
	dl = device_utilities::add_device(Device_Creator((int)DEVICE_IDENTIFIER::GRADIENT, "Test1"));
	Device* ds = static_cast<Device*>(device_utilities::command_device(dl, new Assign(50)));
	testing_util::device_utilities::check_channel(dl, 50);
}
