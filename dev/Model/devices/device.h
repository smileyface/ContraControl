#ifndef MAIN_DEVICE_H
#define MAIN_DEVICE_H

#include <map>
#include<functional>
#include <typeinfo> 

#include "../../Utilities/Logging/logging.h"
#include "../system/timer.h"
#include "../state/state.h"


static uint16_t device_id_pool = 0;
const uint16_t INVALID_DEVICE = UINT16_MAX;


typedef uint16_t Device_Id;

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
	void set_name(std::string new_name)
	{
		device_name = new_name;
	}
	void set_id(Device_Id new_id)
	{
		id = new_id;
	}

	unsigned char get_state_switches()
	{
		return state.switches_pack();
	}
	float get_position()
	{
		return state.position;
	}

	bool operator==(const Device& ld)
	{
		bool type_check = typeid(*this).name() == typeid(ld).name();
		bool device_name = this->device_name == ld.device_name;
		return type_check && device_name;
	}
	Device_State state;
protected:
	
	Device_Id id = INVALID_DEVICE;
	std::string device_name = "INVALID";
};

#endif
