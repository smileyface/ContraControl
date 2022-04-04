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

ipv4_addr get_broadcast(ipv4_addr host_ip, ipv4_addr net_mask)
{
	return host_ip.S_un.S_addr | ~net_mask.S_un.S_addr;
}

ipv4_addr Linux_Network_Interface::get_interface_addr()
{
	char host[NI_MAXHOST];

	getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);

	struct addrinfo* p;
	char s[INET_ADDRSTRLEN];
	inet_ntop(ifa->ifa_addr->sa_family, (struct sockaddr*)ifa->ifa_addr->sa_data, s, sizeof s);

	std::cout << host << " == " << interfaces << std::endl;
	return ipv4_addr(host);
}

ipv4_addr Linux_Network_Interface::get_subnet_mask(SOCKET sock, ipv4_addr host_ip)
{
	char* s = "255.255.255.255";
	int found = 0;

	struct sockaddr_in* sa = (struct sockaddr_in*)ifa->ifa_netmask;
	s = inet_ntoa(sa->sin_addr);
	return ipv4_addr(s);
}

void Linux_Network_Interface::setup_interface()
{
	struct ifaddrs* ifap;
	int found = 0;
	if (getifaddrs(&ifap) == -1)
	{
		perror("getifaddrs");
		exit(EXIT_FAILURE);
	}
	for (ifa = ifap; ifa && !found; ifa = ifa->ifa_next)
	{
		if (ifa->ifa_addr == NULL)
			continue;

		if (strcasecmp(interfaces.c_str(), ifa->ifa_name))
			continue;

		/* IPv4 */
		if (ifa->ifa_addr->sa_family != AF_INET)
			continue;

		found = 1;
	}
	freeifaddrs(ifap);
	if (found == 0)
	{
		status_state.set_error(NETWORK_ERRORS::ADAPTER_ERROR);
		throw NetworkErrorException();
	}
}

NETWORK_ERRORS set_error_state()
{
	switch (errno)
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
		return NETWORK_ERRORS::UNKNOWN_ERROR;
	}
}

Linux_Network_Interface::Linux_Network_Interface()
{
	interfaces = "wlan0";
	local_connections::setup(connections);
}

void Linux_Network_Interface::initalize()
{
	char hostname_temp[50];
	int rc = gethostname(hostname_temp, sizeof(hostname_temp));
	if (rc != 0) 
	{
		status_state.set_error(NETWORK_ERRORS::INVALID_HOSTNAME);
		throw NetworkErrorException();
	}
	hostname = hostname_temp;

	local_connections::setup(connections);
	setup_interface();
	server_running = false;
	setup_connection(local_connections::local, { IPPROTO_TCP, SOCK_STREAM, AF_INET });
	setup_connection(local_connections::broadcast, { IPPROTO_UDP, SOCK_DGRAM, AF_INET });
}

void Linux_Network_Interface::clean_up()
{
	server_running = false;
	pthread_join(server_thread, 0);
	for (auto i = connections.begin(); i != connections.end(); ++i)
	{
		close(i->second.sock);
	}
}

void Linux_Network_Interface::setup_broadcast_socket(Connection& connect, ipv4_addr host_ip)
{
	int broadcast_opt_true = 1;
	if (setsockopt(connect.sock, SOL_SOCKET, SO_BROADCAST, &broadcast_opt_true, sizeof(broadcast_opt_true)) != 0)
	{
		status_state.set_error(set_error_state());
		close(connect.sock);
		connect.sock = INVALID_SOCKET;
		throw NetworkErrorException();
	}
}


void Linux_Network_Interface::setup_connection(Connection_Id connection_name, Socket_Maker maker)
{
	connections[connection_name].sock = socket(maker.sock_family, maker.sock_type, maker.ip_protocol);
	if (connection_name == local_connections::broadcast)
	{
		ipv4_addr subnet_mask = get_subnet_mask(connections[local_connections::local].sock, connections[local_connections::local].address);
		connections[local_connections::broadcast].address = get_broadcast(connections[local_connections::local].address, subnet_mask);
		setup_broadcast_socket(connections[local_connections::broadcast], connections[local_connections::local].address);
	}
	if (connection_name == local_connections::local)
	{
		connections[local_connections::local].address = get_interface_addr();
	}
	network::network_message_interface->push(System_Message(MESSAGE_PRIORITY::DEBUG_MESSAGE, "Interface IP: " + hostname + ": " + connections[local_connections::local].address.get_as_string(), "Network Initalizer"));
}

void Linux_Network_Interface::initalized()
{
	if (hostname == INVALID_HOSTNAME)
	{
		status_state.set_error(NETWORK_ERRORS::INVALID_HOSTNAME);
		throw NetworkErrorException();
	}
	if (connections[local_connections::local].sock < 0 ||
		connections[local_connections::broadcast].sock < 0)
	{
		status_state.set_error(NETWORK_ERRORS::SOCKET_INVALID);
		throw NetworkErrorException();
	}
	status_state.set_status(NETWORK_STATUS::NETWORK_INITALIZED);
}

void Linux_Network_Interface::send(std::string node_id, char* message)
{
	sendto(connections[node_id].sock, message, strlen(message) + 1, 0, (sockaddr*)&connections[node_id].address, sizeof(connections[node_id].address));
}

char* Linux_Network_Interface::listen(Connection_Id Connection_Id)
{

}

#endif //__linux__