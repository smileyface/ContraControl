/*****************************************************************//**
 * \file   device_creator.h
 * \brief  
 * 
 * \author kason
 * \date   August 2023
 *********************************************************************/
#ifndef COMMAND_DEVICE_CREATOR
#define COMMAND_DEVICE_CREATOR

#include "../command.h"
#include "Interfaces/enums/device_type.h"

class Device_Create : public Command
{
public:
	Device_Create();
	~Device_Create();

	Node_Id node;
	Device_Creator device;

	virtual COMMAND_ENUM get_id() { return COMMAND_ENUM::DEVICE_CREATION; }
};

#endif // !COMMAND_DEVICE_CREATOR
