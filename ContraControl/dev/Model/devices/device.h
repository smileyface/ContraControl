
#ifndef MAIN_DEVICE_H
#define MAIN_DEVICE_H

#include <map>
#include<functional>

#include "../../Controller/commands.h"


class Device
{
public:
	Device();
	void run_command(Command command);
	uint16_t get_id() { return id; };
protected:
	void add_command(Command, std::function<void()>);
	COMMAND_ID state = Command::unique_id;
	uint16_t id = UINT16_MAX;
private:
	
};

#endif
