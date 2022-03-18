/*This is where the Linux Network Interface object is defined*/
#ifdef __linux__
#define _GNU_SOURCE
#include <thread>         // std::thread
#include <net/if.h>
#include <iostream>
#include <cstdio>
#include <iostream>
#include <memory>
#include <climits>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/if_link.h>

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
	struct ifaddrs* ifap, * ifa;
	struct sockaddr_in* sa;
	char* s;
	int found = 0;
	char host[NI_MAXHOST];

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

		getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
		ipv4_addr(host);
	}
	return ipv4_addr();
}

ipv4_addr Linux_Network_Interface::get_subnet_mask(SOCKET sock, ipv4_addr host_ip)
{
	struct ifaddrs* ifap, * ifa;
	struct sockaddr_in* sa;
	char* s = "255.255.255.255";
	int found = 0;
	char host[NI_MAXHOST];

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

		sa = (struct sockaddr_in*)ifa->ifa_netmask;
		s = inet_ntoa(sa->sin_addr);
	}
	freeifaddrs(ifap);
	return ipv4_addr(s);
}

NETWORK_ERRORS get_error_state()
{
	std::cout << errno << std::endl;
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
		return NETWORK_ERRORS::NETWORK_CODE_ERROR;
	case EINVAL:
		return NETWORK_ERRORS::SOCKET_INVALID;
	case ENOTSOCK:
		return NETWORK_ERRORS::NETWORK_CODE_ERROR;
	case EACCES:
		return NETWORK_ERRORS::ADAPTER_ERROR;
	case EPROTONOSUPPORT:
		return NETWORK_ERRORS::NETWORK_CODE_ERROR;
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
	local_connections::setup(connections);
	set_my_ip();

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

void Linux_Network_Interface::setup_connection(connection_id connection_name, socket_maker maker)
{
	connections[connection_name].sock = socket(maker.sock_family, maker.sock_type, maker.ip_protocol);
	if (connection_name == local_connections::broadcast)
	{
		ipv4_addr subnet_mask = get_subnet_mask(connections[local_connections::local].sock, connections[local_connections::local].address);
		connections[local_connections::broadcast].address = get_broadcast(connections[local_connections::local].address, subnet_mask);
	}
	if (connection_name == local_connections::local)
	{
		connections[local_connections::local].address = get_interface_addr();
	}
	network::network_message_interface->push(System_Message(MESSAGE_PRIORITY::DEBUG_MESSAGE, "Interface IP: " + hostname + ": " + connections[local_connections::local].address.get_as_string(), "Network Initalizer"));

}

void Linux_Network_Interface::set_my_ip()
{
	struct ifaddrs* ifap, * ifa;
	struct sockaddr_in* sa;
	char* s;
	int found = 0;
	char host[NI_MAXHOST];

	if (getifaddrs(&ifap) == -1) {
		status_state.set_error(get_error_state());
		throw NetworkErrorException();
	}

	for (ifa = ifap; ifa && !found; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr == NULL)
			continue;

		if (strcasecmp(interfaces.c_str(), ifa->ifa_name))
			continue;

		/* IPv4 */
		if (ifa->ifa_addr->sa_family != AF_INET)
			continue;

		getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);

		sa = (struct sockaddr_in*)ifa->ifa_netmask;
		s = inet_ntoa(sa->sin_addr);

		ipv4_addr subnet_mask(s);

		connections[local_connections::local].address = ipv4_addr(host);

		connections[local_connections::broadcast].address = get_broadcast(connections[local_connections::local].address, subnet_mask);
		found = 1;
	}
	//Broadcast NODE_HELLO
	connections[local_connections::broadcast].sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (connections[local_connections::broadcast].sock < 0)
	{
		status_state.set_error(get_error_state());
		throw NetworkErrorException();
	}
}

void Linux_Network_Interface::initalized()
{
	if (connections[local_connections::local].sock > 0 &&
		connections[local_connections::broadcast].sock > 0)
	{
		status_state.set_error(NETWORK_ERRORS::SOCKET_INVALID);
	}
	status_state.set_status(NETWORK_STATUS::NETWORK_INITALIZED);
}

void Linux_Network_Interface::send(std::string node_id, char* message)
{
	sockaddr_in broad_addr;
	memset(&broad_addr, '0', sizeof(&broad_addr));

	broad_addr.sin_family = AF_INET;
	broad_addr.sin_port = htons(DEFAULT_PORT);
	broad_addr.sin_addr.s_addr = inet_addr(connections[node_id].address.get_as_string().c_str());
	sendto(connections[node_id].sock, message, strlen(message) + 1, 0, (sockaddr*)&broad_addr, sizeof(broad_addr));
}

char* Linux_Network_Interface::listen(connection_id connection_id)
{

}

#endif //__linux__