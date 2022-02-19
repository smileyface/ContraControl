#include "../test_utilities/device_utilities.h"
#include "../test_utilities/system_testings.h"
#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"


namespace {
	class Device_Commands_Test : public ::testing::Test {
	protected:
		Device_Label dl;
		virtual void SetUp() {
			system_util::setup();
			device_utilities::setup_node("Test_Node_Local");
			dl = device_utilities::add_device("Test_Node_Local", Device_Creator((int)DEVICE_IDENTIFIER::SWITCH, "Test1"));
			device_utilities::initalize_device(dl);
		}
		virtual void TearDown() {
			system_util::cleanup();
		}

	};

	class Device_Commands_Test_No_Init : public ::testing::Test {
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

TEST_F(Device_Commands_Test, Device_Initalize) {
	Device* ds = create_device_instance(Device_Creator((int)DEVICE_IDENTIFIER::SWITCH, "Results"));
	ds->initalized = true;
	ds->valid = true;

	testing_util::device_utilities::check_state(dl, ds);
}

TEST_F(Device_Commands_Test, Device_On) {
	Device* ds = static_cast<Device*>(device_utilities::command_device(dl, new On()));
	testing_util::device_utilities::check_state(dl, ds);
	system_util::cleanup();
}

TEST_F(Device_Commands_Test, Device_Off) {
	Device* ds = static_cast<Device*>(device_utilities::command_device(dl, new On()));
	testing_util::device_utilities::check_state(dl, ds);

	ds = static_cast<Device*>(device_utilities::command_device(dl, new Off()));
	testing_util::device_utilities::check_state(dl, ds);

	system_util::cleanup();

}