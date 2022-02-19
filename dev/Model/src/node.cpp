#include "../node/node.h"
#include "Network/system_interfaces/network_interface.h"

#include "../Utilities/Utilities/exceptions.h"

Node::Node(Node_Type type)
{
	my_type = type;
	id_pool = 0;
}
Node::Node()
{
	my_type = Node_Type::INVALID;
	id_pool = 0;
}
/**
 Get ready to destroy node.
 */
void Node::clear_node()
{
	//for (auto iter = connections.begin(); iter != connections.end(); iter++)
	//{
	//	delete connections[iter->first];
	//}
	//for (auto iter = devices.begin(); iter != devices.end(); iter++)
	//{
	//	delete devices[iter->first];
	//}
	connections.clear();
	devices.clear();
}
/**
 Add a Device to the node.

 \param device A creator struct that will be used to make the device.
 */
void Node::register_device(Device_Creator device)
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
Device* Node::get_device(Device_Id device)
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
Device* Node::get_device(Device_Name device)
{
	return get_device(name_to_id_map[device]);
}
/**
 Return all devices that the node knows about
 \return The list of Devices.
 */
Device_List Node::get_devices()
{
	Device_List device_ids;
	for (Device_Id_Map::iterator it = devices.begin(); it != devices.end(); ++it)
	{
		device_ids.push_back(it->first);
	}
	return device_ids;
}
/**
 Make the identified node the local node.
 \param id The id of the local node
 */
void Node::initalize_local_control(Node_Id id)
{
	my_id = id;
	network::init_network_interfaces();
}

/**
 * Get the node connected to the local node.
 * \param id Id of the node to get.
 * \return Pointer to the connected node.
 * \throw NodeNotFoundException If node is not a known connection.
 */
Node* Node::get_connection(Node_Id id)
{
	if (connections.find(id) == connections.end())
	{
		throw NodeNotFoundException();
	}
	return connections[id];
}

/**
 * Add node to known connections.
 * \param type Type of the node.
 * \param id The id of the node on the system.
 */
void Node::add_connection(Node_Type type, Node_Id id)
{
	connections.emplace(std::pair<Node_Id, Node*>(id, new Node(type)));
}

/**
 * Get the id of the local node.
 * \return The id.
 */
Node_Id Node::get_id()
{
	return my_id;
}
