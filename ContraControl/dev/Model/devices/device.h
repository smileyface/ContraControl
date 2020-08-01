
#ifndef MAIN_DEVICE_H
#define MAIN_DEVICE_H

#include <map>
#include<functional>

#include "../../Controller/commands.h"

static uint16_t device_id_pool = 0;

class Device
{
public:
	Device() {};
	~Device() {};
	void run_command(Command command);
	uint16_t get_id() { return id; };
protected:
	void register_device(){ id = device_id_pool; device_id_pool++; }
	COMMAND_ID state = Command::unique_id;
	uint16_t id = UINT16_MAX;
private:
	
};

#endif
