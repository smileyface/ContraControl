#ifndef MAIN_DEVICE_H
#define MAIN_DEVICE_H

#include <map>
#include<functional>

#include "../../../Controller/commands.h"

class Device
{
public:
	Device() {};
	~Device() {};
	Device_Id get_id()
	{
		return id;
	};

	std::string get_name()
	{
		return device_name;
	};
	virtual std::string get_full_name()
	{
		std::string device_name = typeid(*this).name();
		return device_name.erase(0, 6) + "::" + get_name();
	}
	void set_state(COMMAND_ID new_state)
	{
		state = new_state;
	};
	void set_name(std::string new_name)
	{
		device_name = new_name;
	}
	void set_id(Device_Id new_id)
	{
		id = new_id;
	}


protected:
	Device_Id id = INVALID_DEVICE;
	std::string device_name = "INVALID";
	COMMAND_ID state = COMMAND_ID::INVALID;
};

#endif
