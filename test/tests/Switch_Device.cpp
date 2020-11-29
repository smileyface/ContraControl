#include "../utilities/device_utilities.h"
#include "../utilities/system_testings.h"

#include "../utilities/pch.h"

TEST(Device_Commands, Switch_Initalize) {
	std::string device = device_utilities::add_device(new Switch_Device());
	Device_State ds;
	ds.initalized = true;
	ds.valid = true;

	device_utilities::check_state(device, ds);

	system_util::cleanup();
}

TEST(Device_Commands, Switch_On) {
	std::string device = device_utilities::add_device(new Switch_Device());

	Device_State ds = device_utilities::command_device(device, new On());
	device_utilities::check_state(device, ds);
	system_util::cleanup();
}

TEST(Device_Commands, Switch_Off) {
	std::string device = device_utilities::add_device(new Switch_Device());

	Device_State ds = device_utilities::command_device(device, new On());
	device_utilities::check_state(device, ds);

	ds = device_utilities::command_device(device, new Off());
	device_utilities::check_state(device, ds);

	system_util::cleanup();
}

TEST(Device_Commands, Switch_Invalid) {
	std::string device = device_utilities::add_device(new Switch_Device());

	device_utilities::command_device(device, new Transition(0, 0));
	device_utilities::check_validity(device, false);

	system_util::cleanup();
}