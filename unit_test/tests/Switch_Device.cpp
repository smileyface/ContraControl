#include "../utilities/device_utilities.h"
#include "../utilities/system_testings.h"
#include "../utilities/test_utilities.h"

#include "../utilities/pch.h"


TEST_F(Device_Commands_Test, Switch_Initalize) {
	device_utilities::create_node("Test_Node_1");
	Device_Label dl = device_utilities::add_device("Test_Node_1", Device_Creator((int)DEVICE_IDENTIFIER::SWITCH, "Test1"));
	device_utilities::initalize_device(dl);
	Device_State ds;
	ds.initalized = true;
	ds.valid = true;

	testing_util::device_utilities::check_state(dl, ds);

	system_util::cleanup();
}

TEST_F(Device_Commands_Test, Switch_On) {
	device_utilities::create_node("Test_Node_1");
	Device_Label dl = device_utilities::add_device("Test_Node_1", Device_Creator((int)DEVICE_IDENTIFIER::SWITCH, "Test1"));
	device_utilities::initalize_device(dl);

	Device_State ds = device_utilities::command_device(dl, new On());
	testing_util::device_utilities::check_state(dl, ds);
	system_util::cleanup();
}

TEST_F(Device_Commands_Test, Switch_Off) {
	device_utilities::create_node("Test_Node_1");
	Device_Label dl = device_utilities::add_device("Test_Node_1", Device_Creator((int)DEVICE_IDENTIFIER::SWITCH, "Test1"));
	device_utilities::initalize_device(dl);

	Device_State ds = device_utilities::command_device(dl, new On());
	testing_util::device_utilities::check_state(dl, ds);

	ds = device_utilities::command_device(dl, new Off());
	testing_util::device_utilities::check_state(dl, ds);

	system_util::cleanup();

}

TEST_F(Device_Commands_Test, Switch_Invalid) {
	device_utilities::create_node("Test_Node_1");
	Device_Label dl = device_utilities::add_device("Test_Node_1", Device_Creator((int)DEVICE_IDENTIFIER::SWITCH, "Test1"));

	device_utilities::command_device(dl, new Transition(0, 0));
	testing_util::device_utilities::check_validity(dl, false);

	system_util::cleanup();
}