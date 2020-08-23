#ifndef MAIN_DEVICE_H
#define MAIN_DEVICE_H

#include <map>
#include<functional>

#include "../../Controller/commands.h"
#include "../../Utilities/Logging/logging.h"

static uint16_t device_id_pool = 0;

class Device
{
public:
	Device();
	~Device();
	uint16_t get_id();
	virtual void run_command(Command* command);
protected:
	void register_device(std::string name);
	COMMAND_ID state = COMMAND_ID::INVALID;
	uint16_t id = UINT16_MAX;
	std::string name = "INVALID";
private:
	
};

#endif
