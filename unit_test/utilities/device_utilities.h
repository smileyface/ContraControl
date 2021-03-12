#ifndef TESTING_DEVICE_UTILITIES
#define TESTING_DEVICE_UTILITIES

#include "../../dev/Model/device.h"
#include "pch.h"
namespace device_utilities
{
	extern int device_in_use;

	Device_State get_nominal_state(Command* command);
	
	/*
	MODEL MANIPULATION
	*/
	/*
	Create node in the model.
	*/
	void create_node(Node_Id);
	/*
	Add a device to the given node in the model. Returns device name.
	*/
	Device_Label add_device(Node_Id, Device_Creator dev);
	/*
	Command a device. Returns the nominal state associated with that command.
	*/
	Device_State command_device(Device_Label label, Command* command);

	Device_State finish_command(Command* command);

	/*
	DEVICE SPECIFIC CHECKS
	*/

	//Check if device state is what is expected
	void check_state(Device_Label label, Device_State expected_state);
	void check_position(std::string device, float position);
	void check_validity(std::string device, bool expect_valid);
	void initalize_device(Device_Label label);
}

#endif // !TESTING_DEVICE_UTILITIES