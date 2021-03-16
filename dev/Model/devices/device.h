#ifndef MAIN_DEVICE_H
#define MAIN_DEVICE_H

#include <map>
#include<functional>
#include <typeinfo> 

#include "../../Controller/commands.h"
#include "../types.h"
#include "../../Utilities/Logging/logging.h"
#include "../system/timer.h"
#include "../state/state.h"


static uint16_t device_id_pool = 0;



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
	void run_command(Command* command)
	{
		command->mangle_state(state);
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
protected:
	
	Device_Id id = INVALID_DEVICE;
	std::string device_name = "INVALID";
	Device_State state;

	virtual void do_command(Command* command) 
	{
		switch(command->get_id())
		{
		case COMMAND_ENUM::INITALIZE:
			set_id(device_id_pool);
			device_id_pool++;
			set_name(static_cast<Initalize*>(command)->name);

			state.initalized = true;
			state.valid = true;
			state.position = 0.0;
			break;
		case COMMAND_ENUM::INVALID:
			state.valid = false;
            break;
        case COMMAND_ENUM::LINEAR_TRANSITION:
        case COMMAND_ENUM::TRANSITION: 
        case COMMAND_ENUM::OFF:
        case COMMAND_ENUM::ON:
            break;
        
		}

	};
};

#endif
