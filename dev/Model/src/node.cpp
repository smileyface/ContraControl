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

void Node::register_device(Device_Creator device)
{
	devices[id_pool] = create_device_instance(device);
	devices[id_pool]->set_id(id_pool);
	name_to_id_map[device.second] = id_pool;
	id_pool++;
}

void Node::remove_device(Device_Id label)
{
	devices.erase(label);
}

Device* Node::get_device(Device_Id device)
{
	if (devices.find(device) == devices.end())
	{
		throw DeviceNotFoundException();
	}
	return devices[device];
}

Device* Node::get_device(Device_Name device)
{
	return get_device(name_to_id_map[device]);
}

Device_List Node::get_devices()
{
	Device_List device_ids;
	for (Device_Id_Map::iterator it = devices.begin(); it != devices.end(); ++it)
	{
		device_ids.push_back(it->first);
	}
	return device_ids;
}

void Node::initalize_local_control(Node_Id id)
{
	my_id = id;
	network::init_network_interfaces();
}

Node* Node::get_connection(Node_Id id)
{
	if (connections.find(id) == connections.end())
	{
		throw NodeNotFoundException();
	}
	return connections[id];
}


void Node::add_connection(Node_Type type, Node_Id id)
{
	connections.emplace(std::pair<Node_Id, Node*>(id, new Node(type)));
}

Node_Id Node::get_id()
{
	return my_id;
}
