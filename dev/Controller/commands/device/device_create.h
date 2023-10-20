/*****************************************************************//**
 * \file   device_create.h
 * \brief  
 * 
 * \author kason
 * \date   August 2023
 *********************************************************************/
#ifndef COMMAND_DEVICE_CREATOR
#define COMMAND_DEVICE_CREATOR

#include "device_command.h"

/**
 * A command for the Model to add a device to a designated Node.
 */
class Device_Create : public Device_Command
{
public:
	Device_Create() = delete;
	~Device_Create();

	/**
	 * Constructor.
	 * \param send_to_node Node that the device will be created on.
	 * \param id Id for the newly created device.
	 * \param name Common name for the newly created device.
	 */
	Device_Create(Node_Id send_to_node, Device_Id id, Device_Name name);

	/**
	 * \return ID of the node that the device will be created on.
	 */
	Node_Id node;
	/**
	 * ID of the device and the common name to be created on the node.
	 */
	Device_Creator device;

	virtual COMMAND_ENUM get_id() { return COMMAND_ENUM::DEVICE_CREATION; }
};

#endif // !COMMAND_DEVICE_CREATOR
