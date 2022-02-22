#ifndef TESTING_DEVICE_UTILITIES
#define TESTING_DEVICE_UTILITIES

#include "../../dev/Controller/commands.h"
#include "../../dev/Interfaces/Interfaces/types/device_label.h"
#include "../../dev/Model/device.h"

#include "pch.h"
namespace device_utilities
{
	extern int device_in_use;
	extern Node_Id node_handle;

	Device* get_nominal_state(DEVICE_IDENTIFIER device, Command* command);
	Device* get_nominal_state_no_init(DEVICE_IDENTIFIER device, Command* command);
	
	/*
	MODEL MANIPULATION
	*/

	void start_test_environment();
	/*
	Add a device to the given node in the model. Returns device name.
	*/
	Device_Label add_device(Device_Creator);
	/*
	Remove device from a node;
	*/
	void remove_device(Device_Label);
	/*
	Command a device. Returns the nominal state associated with that command.
	*/
	Device* command_device(Device_Label label, Command* command);

	Device* command_device_no_init(Device_Label label, Command* command);

	Device* finish_command(Device_Label label, Command* command);

	void initalize_device(Device_Label label);

}

#include"../test_utilities/system_testings.h"

#endif // !TESTING_DEVICE_UTILITIES