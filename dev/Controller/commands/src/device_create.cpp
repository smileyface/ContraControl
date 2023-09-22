#include "../device/device_create.h"

Device_Create::Device_Create() :
	node("")
{ 
	device = Device_Creator(INVALID_DEVICE, "");
}

Device_Create::Device_Create(Node_Id send_to_node, Device_Id id, Device_Name name) :
	node(send_to_node)
{
	device = Device_Creator(id, name);
}

Device_Create::~Device_Create()
{ }
