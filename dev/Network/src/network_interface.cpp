#include <string>
#include <iostream>
#include "../system_interfaces/network_interface.h"

Network_Interface::~Network_Interface()
{
}

void Network_Interface::set_client()
{
	is_server = false;
}

void Network_Interface::set_hostname(const std::string& host)
{
	hostname = host;
}

void Network_Interface::set_interface(const std::string& i)
{
	interfaces = i;
	LOG_DEBUG("Interfaces is " + i);
}

void Network_Interface::set_network_state(NETWORK_STATUS status)
{
	status_state.set_status(status);
}

Connection Network_Interface::get_connection(Connection_Id connection)
{
	return connections[connection];
}

std::string Network_Interface::get_hostname()
{
	return hostname;
}
bool Network_Interface::server()
{
	return is_server == true;
}

bool Network_Interface::client()
{
	return is_server == false;
}

void Network_Interface::set_server()
{
	is_server = true;
}

Network_Status_State Network_Interface::get_status()
{
	return status_state;
}