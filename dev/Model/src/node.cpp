#include "../node/node.h"
#include "../model_main.h"

#include "../Utilities/Utilities/exceptions.h"

Node::Node() :
	my_type(NODE_TYPE::INVALID),
	id_pool(0),
	my_id("")
{ }

Node::Node(NODE_TYPE type, Node_Id id) :
	my_type(type),
	id_pool(0),
	my_id(id)
{ }

Node::~Node()
{
	for(auto i = devices.begin(); i != devices.end(); i++)
	{
		delete devices[i->first];
	}
	devices.clear();
	//Nodes memory is handled in the Model
	connections.clear();
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
	delete devices[label];
	devices.erase(label);
}

Device* Node::get_device(Device_Id device)
{
	Device* found_device = nullptr;
	if (devices.count(device))
	{
		found_device = devices[device];
	}
	else
	{
		LOG_ERROR("Device " + std::to_string(device) + " Not Found", "Node");
	}
	return found_device;
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


void Node::add_connection(Node* node_connection)
{
	connections.emplace(std::pair<Node_Id, Node*> (node_connection->get_id(), node_connection));
}

void Node::remove_connection(Node_Id id)
{
	connections.erase(id);
}

Node_Id Node::get_id()
{
	return my_id;
}
