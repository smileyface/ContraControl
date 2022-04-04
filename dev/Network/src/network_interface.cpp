#include <string>
#include <iostream>
#include "../system_interfaces/network_interface.h"

void Network_Interface::set_client()
{
	is_server = false;
}

void Network_Interface::set_hostname(std::string host)
{
	hostname = host;
}

void Network_Interface::set_interface(std::string i)
{
	interfaces = i;
	//The network messenger interface is not set up yet.
	System_Messages::get_instance()->push(System_Message(MESSAGE_PRIORITY::DEBUG_MESSAGE, "Interfaces is " + i, "Set Network Interface"));
}

void Network_Interface::set_server()
{
	is_server = true;
}

Network_Status_State Network_Interface::get_status()
{
	return status_state;
}
