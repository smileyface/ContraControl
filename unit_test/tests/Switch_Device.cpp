#include "../utilities/device_utilities.h"
#include "../utilities/system_testings.h"
#include "../utilities/test_utilities.h"

#include "../utilities/pch.h"


namespace {
	class Switch_Commands_Test : public ::testing::Test {
	protected:
		Device_Label dl;
		virtual void SetUp() {
			system_util::setup();
			device_utilities::create_node("Test_Node_1");
			dl = device_utilities::add_device("Test_Node_1", Device_Creator((int)DEVICE_IDENTIFIER::SWITCH, "Test1"));
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
			device_utilities::create_node("Test_Node_1");
			dl = device_utilities::add_device("Test_Node_1", Device_Creator((int)DEVICE_IDENTIFIER::SWITCH, "Test1"));
		}
		virtual void TearDown() {
			system_util::cleanup();
		}

	};
}

TEST_F(Switch_Commands_Test, Switch_Initalize) {
	Device_State ds;
	ds.initalized = true;
	ds.valid = true;

	testing_util::device_utilities::check_state(dl, ds);
}

TEST_F(Switch_Commands_Test, Switch_On) {
	Device_State ds = device_utilities::command_device(dl, new On());
	testing_util::device_utilities::check_state(dl, ds);
	system_util::cleanup();
}

TEST_F(Switch_Commands_Test, Switch_Off) {
	Device_State ds = device_utilities::command_device(dl, new On());
	testing_util::device_utilities::check_state(dl, ds);

	ds = device_utilities::command_device(dl, new Off());
	testing_util::device_utilities::check_state(dl, ds);

	system_util::cleanup();

}

TEST_F(Switch_Commands_Test_No_Init, Switch_Invalid) {
	device_utilities::command_device(dl, new Transition(0, 0));
	testing_util::device_utilities::check_validity(dl, false);

	system_util::cleanup();
}