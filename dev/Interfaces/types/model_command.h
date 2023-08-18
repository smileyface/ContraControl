/*****************************************************************//**
 * \file   model_command.h
 * \brief
 *
 * \author kason
 * \date   June 2021
 *********************************************************************/
#ifndef INTERFACE_MODEL_COMMAND_TYPE
#define INTERFACE_MODEL_COMMAND_TYPE

#include <vector>

#include "Interfaces/types/device_label.h"
#include "../../../Controller/commands.h"

 /**
	 A command to add to this step of the model.
  */
class Model_Command {
public:
	/**
	 \param device_label Label that maps to the device to run.
	 \param cmd Command to run.
	 */
	Model_Command(Device_Label device_label, Command* cmd)
	{
		label = device_label;
		command = cmd;
	};
	/**
	 Label that maps to the device to run.
	 */
	Device_Label label;
	/**
	 Command to run.
	 */
	Command* command;
};

#endif // !INTERFACE_MODEL_COMMAND_TYPE


