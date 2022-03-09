#include <string>

#include "../system_interfaces/network_interface.h"

void Network_Interface::set_client()
{
	is_server = false;
}

void Network_Interface::set_server()
{
	is_server = true;
}

Network_Status_State Network_Interface::get_status()
{
	return status_state;
}





