#include "../node/node.h"

#include "../Utilities/Utilities/exceptions.h"

Node::Node(NODE_TYPE type)
{
	my_type = type;
	id_pool = 0;
}
Node::Node()
{
	my_type = NODE_TYPE::INVALID;
	id_pool = 0;
}
Node::~Node()
{
	for(auto device = devices.begin(); device != devices.end();device++)
	{
		delete device->second;
	}
	devices.clear();
	for(auto conn = connections.begin(); conn != connections.end(); conn++)
	{
		delete conn->second;
	}
	connections.clear();

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

void Node::remove_device(Device_Id label)
{
	delete devices[label];
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
}

Node* Node::get_connection(Node_Id id)
{
	if (connections.find(id) == connections.end())
	{
		throw NodeNotFoundException();
	}
	return connections[id];
}


void Node::add_connection(NODE_TYPE type, Node_Id id)
{
	connections.emplace(std::pair<Node_Id, Node*>(id, new Node(type)));
}

void Node::remove_connection(Node_Id id)
{
	delete connections[id];
}

Node_Id Node::get_id()
{
	return my_id;
}
