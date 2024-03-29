﻿/*This is where the Linux Network Interface object is defined*/
#ifdef __linux__
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <iostream>

#include "../system_interfaces/linux_network_interface.h"
#include "Utilities/exceptions.h"
#include "../network_main.h"

typedef void* (*THREADFUNCPTR)(void*);

pthread_t server_thread;

IPV4_Addr get_broadcast(IPV4_Addr host_ip, IPV4_Addr net_mask)
{
	IPV4_Addr bcast;
	bcast = host_ip.S_un.S_addr | ~net_mask.S_un.S_addr;
	return bcast;
}

IPV4_Addr Linux_Network_Interface::get_interface_addr()
{
	char host[NI_MAXHOST];

	getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);

	LOG_DEBUG(std::string(ifa->ifa_name) + " " + host);
	return IPV4_Addr(host);
}

IPV4_Addr Linux_Network_Interface::get_subnet_mask(SOCKET sock, IPV4_Addr host_ip)
{
	char* s = (char*)"255.255.255.255";
	int found = 0;

	struct sockaddr_in* sa = (struct sockaddr_in*) ifa->ifa_netmask;
	s = inet_ntoa(sa->sin_addr);
	return IPV4_Addr(s);
}

void Linux_Network_Interface::setup_interface()
{
	struct ifaddrs* ifap;
	int found = 0;

	if(getifaddrs(&ifap) == -1)
	{
		perror("getifaddrs");
		exit(EXIT_FAILURE);
	}

	ifa = ifap;

	LOG_DEBUG("Interface trying to find is " + interfaces);
	while(ifa && !found)
	{
		if(ifa->ifa_addr->sa_family == AF_INET)
		{
			char host[NI_MAXHOST];
			getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
			LOG_DEBUG(std::string(ifa->ifa_name) + " " + host);
		}
		if(ifa->ifa_addr != NULL && strcasecmp(interfaces.c_str(), ifa->ifa_name) == 0 && ifa->ifa_addr->sa_family == AF_INET)
		{
			found = 1;
			break;
		}
		ifa = ifa->ifa_next;
	}
	freeifaddrs(ifap);
	if(found == 0)
	{
		LOG_ERROR("No Adapter Found", "Linux Network");
		status_state.set_error(NETWORK_ERRORS::ADDRESS_ERROR);
		return;
	}
}

NETWORK_ERRORS set_error_state()
{
	switch(errno)
	{
	case EISCONN:
		return NETWORK_ERRORS::SOCKET_BUSY;
		break;
		//This is only essential for using ipv6. So I'm ignoring.
	case EAFNOSUPPORT:
		break;
	case EADDRINUSE:
		return NETWORK_ERRORS::SOCKET_BUSY;
	case EBADF:
		return NETWORK_ERRORS::SOCKET_INVALID;
	case EINVAL:
		return NETWORK_ERRORS::NETWORK_OPTION_ERROR;
	case ENOTSOCK:
		return NETWORK_ERRORS::NETWORK_CODE_ERROR;
	case EACCES:
		return NETWORK_ERRORS::ADAPTER_ERROR;
	case EPROTONOSUPPORT:
		return NETWORK_ERRORS::NETWORK_CODE_ERROR;
	case ENOPROTOOPT:
		return NETWORK_ERRORS::NETWORK_OPTION_ERROR;
	default:
		{
		std::string msg("Unknown network error "  + std::to_string(errno) + " caught");
		LOG_ERROR(msg, "Linux Network");
		return NETWORK_ERRORS::UNKNOWN_ERROR;
		}
	}
	return NETWORK_ERRORS::UNKNOWN_ERROR;
}

Linux_Network_Interface::Linux_Network_Interface()
{

	interfaces = "lo";
	local_connections::setup(connections);
}

Linux_Network_Interface::~Linux_Network_Interface()
{
}
void Linux_Network_Interface::initalize()
{
	char hostname_temp[50];
	int rc = gethostname(hostname_temp, sizeof(hostname_temp));
	if(rc != 0)
	{
		status_state.set_error(NETWORK_ERRORS::INVALID_HOSTNAME);
		return;
	}
	hostname = hostname_temp;

	local_connections::setup(connections);
	setup_interface();
	if(status_state.status != NETWORK_STATUS::NETWORK_ERROR)
	{
		server_running = false;
		setup_connection(local_connections::local, { IPPROTO_TCP, SOCK_STREAM, AF_INET });
		setup_connection(local_connections::broadcast, { IPPROTO_UDP, SOCK_DGRAM, AF_INET });
	}
}

void Linux_Network_Interface::clean_up()
{
	server_running = false;
	pthread_join(server_thread, 0);
	for(auto i = connections.begin(); i != connections.end(); ++i)
	{
		close(i->second.sock);
	}
}

void Linux_Network_Interface::setup_broadcast_socket(Connection& connect, IPV4_Addr host_ip)
{
	int broadcast_opt_true = 1;
	if(setsockopt(connect.sock, SOL_SOCKET, SO_BROADCAST, &broadcast_opt_true, sizeof(broadcast_opt_true)) != 0)
	{
		status_state.set_error(set_error_state());
		close(connect.sock);
		connect.sock = INVALID_SOCKET;
		return;
	}
}

void Linux_Network_Interface::setup_connection(Connection_Id connection_name, Socket_Maker maker)
{
	connections[connection_name].sock = socket(maker.sock_family, maker.sock_type, maker.ip_protocol);
	if(connection_name == local_connections::broadcast)
	{
		IPV4_Addr subnet_mask = get_subnet_mask(connections[local_connections::local].sock, connections[local_connections::local].address);
		connections[local_connections::broadcast].address = get_broadcast(connections[local_connections::local].address, subnet_mask);
		setup_broadcast_socket(connections[local_connections::broadcast], connections[local_connections::local].address);
		LOG_DEBUG("Broadcast IP: " + connections[local_connections::broadcast].address.get_as_string());
	}
	if(connection_name == local_connections::local)
	{
		connections[local_connections::local].address = get_interface_addr();
		LOG_DEBUG("Interface IP: " + hostname + ": " + connections[local_connections::local].address.get_as_string());
	}
}

void Linux_Network_Interface::initalized()
{
	if(hostname == INVALID_HOSTNAME)
	{
		status_state.set_error(NETWORK_ERRORS::INVALID_HOSTNAME);
		LOG_ERROR("Hostname Invalid", "Linux Network");
		return;
	}
	if(connections[local_connections::local].sock < 0 ||
	   connections[local_connections::broadcast].sock < 0)
	{
		status_state.set_error(NETWORK_ERRORS::SOCKET_INVALID);
		LOG_ERROR("Invalid Socket", "Linux Network");
		return;
	}
	status_state.set_status(NETWORK_STATUS::NETWORK_INITALIZED);
}

void Linux_Network_Interface::send(std::string node_id, char* message)
{
	sendto(connections[node_id].sock, message, strlen(message) + 1, 0, (sockaddr*) &connections[node_id].address, sizeof(connections[node_id].address));
}

char* Linux_Network_Interface::listen(Connection_Id Connection_Id)
{ 
	return 0;
}

#endif //__linux__