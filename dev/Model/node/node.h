/*****************************************************************//**
 * \file   node.h
 * \brief  
 * 
 * \author kason
 * \date   May 2021
 *********************************************************************/
#ifndef MODEL_NODE_H
#define MODEL_NODE_H


#include "../device.h"
#include "../Utilities/Utilities/exceptions.h"
#include "Network/connections.h"

/**
 Type of node, such as UI, GENERIC_HARDWARE or R-PI
 */
enum class Node_Type : uint8_t
{
	/**
	 A Tester node.
	 */
	TEST,
	/**
	 A UI node. Connects to virtual devices
	 */
	UI,
	/**
	 Invalid node. Undefined.
	 */
	INVALID
};

/**
 A node, which represents a computer, such as a Raspberry Pi, or other command device. 
 */
class Node
{
public:
	/**
	 Create a node instance by giving it a type.

	 \param type The type of node.
	 */
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
	/**
	 Add a Device to the node. 

	 \param device A creator struct that will be used to make the device.
	 */
	void register_device(Device_Creator device)
	{
		devices[id_pool] = create_device_instance(device);
		devices[id_pool]->set_id(id_pool);
		name_to_id_map[device.second] = id_pool;
		id_pool++;
	}

	/**
	 Return a pointer to a device requested by Device_Id

	 \param device An Id struct that points to a specific device.
	 \return Pointer to the device.
	 \throws DeviceNotFoundException if node does not know about the device
	 */
	Device* get_device(Device_Id device)
	{
		if (devices.find(device) == devices.end())
		{
			throw DeviceNotFoundException();
		}
		return devices[device];
	}
	/**
	 Return a pointer to a device requested by Device_Name
	 \param device A name that points to a specific device.
	 \return Pointer to the device.
	 \throws DeviceNotFoundException if node does not know about the device
	 */
	Device* get_device(Device_Name device)
	{
		return get_device(name_to_id_map[device]);
	}
	/**
	 Return all devices that the node knows about
	 \return The list of Devices.
	 */
	Device_List get_devices()
	{
		Device_List device_ids;
		for (Device_Id_Map::iterator it = devices.begin(); it != devices.end(); ++it)
		{
			device_ids.push_back(it->first);
		}
		return device_ids;
	}
private:
	Connection_List connections;
	Device_Id_Map devices;
	std::map<Device_Name, Device_Id> name_to_id_map;
	Node_Type my_type;
	Device_Id id_pool;
};

/**
 A map to hold a node by a given ID
 */
typedef std::map<Node_Id, Node*> Node_Map;

#endif // !MODEL_NODE_H
