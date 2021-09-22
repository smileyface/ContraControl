#include "../test_utilities/device_utilities.h"
#include "../test_utilities/system_testings.h"
#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"


namespace {
	class Switch_Commands_Test : public ::testing::Test {
	protected:
		Device_Label dl;
		virtual void SetUp() {
			system_util::setup();
			device_utilities::setup_node("Test_Node_Local", Node_Type::TEST);
			dl = device_utilities::add_device("Test_Node_Local", Device_Creator((int)DEVICE_IDENTIFIER::SWITCH, "Test1"));
			device_utilities::initalize_device(dl);
		}
		virtual void TearDown() {
			system_util::cleanup();
		}

	};

	class Switch_Commands_Test_No_Init : public ::testing::Test {
	protected:
		Device_Label dl;
		virtual void SetUp() {
			system_util::setup();
			device_utilities::setup_node("Test_Node_Local", Node_Type::TEST);
			dl = device_utilities::add_device("Test_Node_Local", Device_Creator((int)DEVICE_IDENTIFIER::SWITCH, "Test1"));
		}
		virtual void TearDown() {
			system_util::cleanup();
		}

	};
}

TEST_F(Switch_Commands_Test, Switch_Initalize) {
	Switch_Device* ds = new Switch_Device();
	ds->initalized = true;
	ds->valid = true;

	testing_util::device_utilities::check_state(dl, ds);
}

TEST_F(Switch_Commands_Test, Switch_On) {
	Switch_Device* ds = static_cast<Switch_Device*>(device_utilities::command_device(dl, new On()));
	testing_util::device_utilities::check_state(dl, ds);
	system_util::cleanup();
}

TEST_F(Switch_Commands_Test, Switch_Off) {
	Switch_Device* ds = static_cast<Switch_Device*>(device_utilities::command_device(dl, new On()));
	testing_util::device_utilities::check_state(dl, ds);

	ds = static_cast<Switch_Device*>(device_utilities::command_device(dl, new Off()));
	testing_util::device_utilities::check_state(dl, ds);

	system_util::cleanup();

}

TEST_F(Switch_Commands_Test_No_Init, Switch_Invalid) {
	device_utilities::command_device(dl, new Transition(0, 0));
	testing_util::device_utilities::check_validity(dl, false);

	system_util::cleanup();
}