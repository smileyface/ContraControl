#ifndef TESTING_DEVICE_UTILITIES
#define TESTING_DEVICE_UTILITIES

#include "../../dev/Model/device.h"
#include "pch.h"
namespace device_utilities
{
	extern int device_in_use;

	device_state get_nominal_state(Command* command);
	
	/*
	MODEL MANIPULATION
	*/

	/*
	Add a device to the model. Returns device name.
	*/
	std::string add_device(Device* dev);
	/*
	Command a device. Returns the nominal state associated with that command.
	*/
	device_state command_device(std::string device_id, Command* command);

	device_state finish_command(Command* command);

	/*
	DEVICE SPECIFIC CHECKS
	*/

	//Check if device state is what is expected
	void check_state(std::string device, device_state expected_state);
	void check_position(std::string device, float position);
	void check_validity(std::string device, bool expect_valid);
}

#endif // !TESTING_DEVICE_UTILITIES