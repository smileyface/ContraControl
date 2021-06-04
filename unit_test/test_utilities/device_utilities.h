#ifndef TESTING_DEVICE_UTILITIES
#define TESTING_DEVICE_UTILITIES

#include "../../dev/Model/node/node.h"
#include "../../dev/Controller/commands.h"
#include "../../dev/Interfaces/Interfaces/types/device_label.h"
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
	Device_Label add_device(Node_Id, Device_Creator);
	/*
	Command a device. Returns the nominal state associated with that command.
	*/
	Device_State command_device(Device_Label label, Command* command);

	Device_State finish_command(Command* command);

	void initalize_device(Device_Label label);
}

#include"../test_utilities/system_testings.h"

#endif // !TESTING_DEVICE_UTILITIES