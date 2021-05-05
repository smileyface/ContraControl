/*****************************************************************//**
 * \file   node.h
 * \brief  
 * 
 * \author kason
 * \date   May 2021
 *********************************************************************/

#ifndef MODEL_NODE_H
#define MODEL_NODE_H

#include <map>			// std::map

#include "../device.h"
#include "../../Interfaces/Network/connections.h"
#include "../../Utilities/exceptions.h"

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
		id_pool = 0;
	}
	Node() 
	{
		my_type = Node_Type::INVALID;
		id_pool = 0;
	}
	void register_device(Device_Creator device)
	{
		devices[id_pool] = create_device_instance(device);
		devices[id_pool]->set_id(id_pool);
		name_to_id_map[device.second] = id_pool;
		id_pool++;
	}

	Device* get_device(Device_Id device)
	{
		if (devices.find(device) == devices.end())
		{
			throw DeviceNotFoundException();
		}
		return devices[device];
	}
	Device* get_device(Device_Name device)
	{
		return devices[name_to_id_map[device]];
	}
	std::vector<Device_Id> get_devices()
	{
		std::vector<Device_Id> device_ids;
		for (std::map<Device_Id, Device*>::iterator it = devices.begin(); it != devices.end(); ++it)
		{
			device_ids.push_back(it->first);
		}
		return device_ids;
	}
private:
	Connection connections;
	std::map<Device_Id, Device*> devices;
	std::map<Device_Name, Device_Id> name_to_id_map;
	Node_Type my_type;
	Device_Id id_pool;
};


typedef std::string Node_Id; ///<An Identifier for a node
typedef std::map<Node_Id, Node*> Node_Map; ///<A map to hold a node by a given ID

#endif // !MODEL_NODE_H
