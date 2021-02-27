#ifndef MODEL_NODE_H
#define MODEL_NODE_H

#include <map>
#include <string>
#include "../device.h"
#include "../../Interfaces/Network/connections.h"

enum class Node_Type : uint8_t
{
	TEST,
	UI,
	INVALID
};

class Node
{
public:
	Node(Node_Type type)
	{
		my_type = type;
	}
	Node() 
	{
		my_type = Node_Type::INVALID;
	}
	void register_device(Device* device)
	{
		devices[device->get_id()] = device;
		name_to_id_map[device->get_name()] = device->get_id();
	}
	void run_command(Device* device, Command* command)
	{
		if (devices.find(device->get_id()) != devices.end())
		{
			device->run_command(command);
		}
	}
	Device* get_device(Device_Id device)
	{
		return devices[device];
	}
	Device* get_device(Device_Name device)
	{
		return devices[name_to_id_map[device]];
	}
private:
	Connection connections;
	std::map<Device_Id, Device*> devices;
	std::map<Device_Name, Device_Id> name_to_id_map;
	Node_Type my_type;
};

#endif // !MODEL_NODE_H
