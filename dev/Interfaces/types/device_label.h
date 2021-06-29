#ifndef INTERFACE_TYPE_DEVICE_LABEL
#define INTERFACE_TYPE_DEVICE_LABEL

#include "../../Model/node/node.h"

class Device_Label
{
public:
	Device_Label() {};
	Device_Label(Node_Id node, Device_Id device)
	{
		node_label = node;
		device_label = device;
	}
	bool operator==(const Device_Label& rhs)
	{
		return rhs.device_label == device_label && rhs.node_label == node_label;
	}
	Node_Id get_node_id()
	{
		return node_label;
	}
	Device_Id get_device_id()
	{
		return device_label;
	}
private:
	Node_Id node_label;
	Device_Id device_label;
};

#endif