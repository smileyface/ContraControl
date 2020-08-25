#ifndef MAIN_DEVICE_H
#define MAIN_DEVICE_H

#include <map>
#include<functional>

#include "../../Controller/commands.h"




class Device
{
public:
	Device() {};
	~Device() {};
	uint16_t get_id()
	{
		return id;
	};

	std::string get_name()
	{
		return name;
	};
	void set_state(COMMAND_ID new_state)
	{
		state = new_state;
	};
	void set_name(std::string new_name)
	{
		name = new_name;
	}
	void set_id(uint16_t new_id)
	{
		id = new_id;
	}

	virtual std::string type_id() { return "Device"; };

protected:
	uint16_t id = UINT16_MAX;
	std::string name = "INVALID";
	COMMAND_ID state = COMMAND_ID::INVALID;
};

#endif
