#include "../utilities/device_utilities.h"
#include "../utilities/system_testings.h"

#include "../utilities/pch.h"

TEST(Device_Commands, Switch_Initalize) {
	device_utilities::create_node("Test_Node_1");
	Device_Label dl = device_utilities::add_device("Test_Node_1", new Switch_Device());
	device_utilities::initalize_device(dl);
	Device_State ds;
	ds.initalized = true;
	ds.valid = true;

	device_utilities::check_state(dl, ds);

	system_util::cleanup();
}

TEST(Device_Commands, Switch_On) {
	FAIL() << "Need to be implemented";
	/*std::string device = device_utilities::add_device(new Switch_Device());
	device_utilities::initalize_device(device);

	Device_State ds = device_utilities::command_device(device, new On());
	device_utilities::check_state(device, ds);
	system_util::cleanup();*/
}

TEST(Device_Commands, Switch_Off) {
	FAIL() << "Need to be implemented";
	/*std::string device = device_utilities::add_device(new Switch_Device());
	device_utilities::initalize_device(device);

	Device_State ds = device_utilities::command_device(device, new On());
	device_utilities::check_state(device, ds);

	ds = device_utilities::command_device(device, new Off());
	device_utilities::check_state(device, ds);

	system_util::cleanup();*/
}

TEST(Device_Commands, Switch_Invalid) {
	FAIL() << "Need to be implemented";
	/*std::string device = device_utilities::add_device(new Switch_Device());

	device_utilities::command_device(device, new Transition(0, 0));
	device_utilities::check_validity(device, false);

	system_util::cleanup();*/
}