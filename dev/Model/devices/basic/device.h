#ifndef MAIN_DEVICE_H
#define MAIN_DEVICE_H

#include <map>
#include<functional>
#include <typeinfo> 

#include "../../../Controller/commands.h"
#include "../../types.h"
#include "../../../Utilities/Logging/logging.h"
#include "../../system/timer.h"


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
	void set_state(COMMAND_ID unique_id)
	{
		state = unique_id;
	};
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
		if (command->get_unique_id() == COMMAND_ID::INVALID)
		{

		}
		else
		{
			do_command(command);
			set_state(command->get_unique_id());
			add_command_to_log(command);
		}
	}

protected:
	Device_Id id = INVALID_DEVICE;
	std::string device_name = "INVALID";
	COMMAND_ID state;

	virtual void do_command(Command* command) 
	{
		if (command->get_unique_id() == COMMAND_ID::INITALIZE)
		{
			set_id(device_id_pool);
			device_id_pool++;
			set_name(static_cast<Initalize*>(command)->name);
		}
	};

	void add_command_to_log(Command* command)
	{
		sys_log::log(LOG_PRIORITY::DEBUG, command->get_log_entry(), get_full_name());
	}
};

#endif
