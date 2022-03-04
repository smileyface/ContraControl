﻿/*This is where the Linux Network Interface object is defined*/
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

#include "Network/system_interfaces/linux_network_interface.h"
#include "../Utilities/Utilities/exceptions.h"

typedef void* (*THREADFUNCPTR)(void*);

pthread_t server_thread;

std::string interfaces = "wlan0";

const std::vector<std::string> explode(const std::string& s, const char& c)
{
	std::string buff{ "" };
	std::vector<std::string> v;

	for (auto n : s)
	{
		if (n != c) buff += n; else
			if (n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if (buff != "") v.push_back(buff);

	return v;
}

ipv4_addr get_broadcast(ipv4_addr host_ip, ipv4_addr net_mask)
{
	return host_ip.S_un.S_addr | ~net_mask.S_un.S_addr;
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

void Linux_Network_Interface::connect_to_server(ipv4_addr addr)
{
	serv_addr.sin_addr.s_addr = inet_addr(addr.get_as_string().c_str());
	int result = connect(sock, (struct sockaddr*)&serv_addr.sin_addr, sizeof(serv_addr));
	if (result != 0)
	{
		status_state.set_error(get_error_state());
	}
}

void Linux_Network_Interface::initalize()
{
	/* creates an UN-named socket inside the kernel and returns
	* an integer known as socket descriptor
	* This function takes domain/family as its first argument.
	* For Internet family of IPv4 addresses we use AF_INET
	*/
	sock = socket(sock_family, sock_type, ip_protocol);
	
	set_my_ip();

	//broadcast_ip = get_broadcast(host_ip, );

	server_running = false;
}

void Linux_Network_Interface::clean_up()
{
	server_running = false;
	pthread_join(server_thread, 0);
	close(sock);
}

void Linux_Network_Interface::set_my_ip()
{
	struct ifaddrs* ifap, * ifa;
	struct sockaddr_in* sa;
	char* s;
	int found = 0;
	char host[NI_MAXHOST];

	if (getifaddrs(&ifap) == -1) {
		perror("getifaddrs");
		exit(EXIT_FAILURE);
	}

	for (ifa = ifap; ifa && !found; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr == NULL)
			continue;

		if (strcasecmp(interfaces.c_str(), ifa->ifa_name))
			continue;

		/* IPv4 */
		if (ifa->ifa_addr->sa_family != AF_INET)
			continue;
		getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host , NI_MAXHOST, NULL, 0, NI_NUMERICHOST);

		host_ip = ipv4_addr(host);

		sa = (struct sockaddr_in*)ifa->ifa_netmask;
		s = inet_ntoa(sa->sin_addr);

		subnet_mask = s;

		broadcast_ip = get_broadcast(host_ip, subnet_mask);
		found = 1;
	}

	freeifaddrs(ifap);



	/*THIS WILL DO FOR NOW*/
	std::string cmd = "/sbin/ifconfig " + interfaces + " | awk '/inet /{ print $2;} '";
	std::array<char, 128> buffer;
	ipv4_addr result;
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
	if (!pipe)
	{
		throw std::runtime_error("popen() failed!");
	}
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
	{
		std::string str_result(buffer.data());
		ipv4_addr temp_addr(str_result);
		host_ip = temp_addr;
	}
}

/**
* \todo handle multiple interfaces.
*/
ipv4_addr get_subnet_mask(SOCKET sock, ipv4_addr host_ip, Network_Status_State& status_state)
{
	std::string cmd = "/sbin/ifconfig " + interfaces + " | awk '/(M|m)ask(:)? /{ print $4;} '";
	std::array<char, 128> buffer;
	ipv4_addr result;
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
	if (!pipe) 
	{
		throw std::runtime_error("popen() failed!");
	}
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) 
	{
		std::string str_result(buffer.data());
		ipv4_addr temp_addr(str_result);
		result = temp_addr;
	}
	return result;
}


void Linux_Network_Interface::scan_for_server()
{
	//Broadcast NODE_HELLO
	SOCKET broadcast_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (broadcast_sock < 0)
	{
		status_state.set_error(get_error_state());
		throw NetworkErrorException();
	}
	sockaddr_in broad_addr;
	memset(&broad_addr, '0', sizeof(&broad_addr));

	broad_addr.sin_family = AF_INET;
	broad_addr.sin_port = htons(DEFAULT_PORT);

	int broadcastEnable = 1;
	int ret = setsockopt(broadcast_sock, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));

	//TODO: Turn this into a real node hello packet.
	/*Testing things for now*/
	char sendMSG[] = "NODE_HELLO";



	char recvbuff[50] = "";

	int recvbufflen = 50;

	sendto(broadcast_sock, sendMSG, strlen(sendMSG) + 1, 0, (sockaddr*)&broad_addr, sizeof(broad_addr));
	//send_periodic(broadcast_sock, NODE_HELLO, 2000, till_found);

	close(broadcast_sock);

}

void Linux_Network_Interface::initalized()
{
	if (sock > 0)
	{
		status_state.set_error(NETWORK_ERRORS::SOCKET_INVALID);
	}
	status_state.set_status(NETWORK_STATUS::NETWORK_INITALIZED);
}

void Linux_Network_Interface::server_start()
{
	server_running = true;
	int err = pthread_create(&server_thread, NULL, (THREADFUNCPTR)&Linux_Network_Interface::server_listen, new Linux_Network_Interface());
	if (err)
	{
		status_state.set_error(NETWORK_ERRORS::SERVER_CANNOT_START);
		throw NetworkErrorException();
	}
}

void Linux_Network_Interface::server_listen()
{
	/* The call to the function "listen()" with second argument as 10 specifies
	 * maximum number of client connections that server will queue for this listening
	 * socket.
	 */
		listen(sock, 10);


	while (server_running)
	{
		sockaddr* address;
		socklen_t address_size = sizeof(address);
		/* In the call to accept(), the server is put to sleep and when for an incoming
		 * client request, the three way TCP handshake* is complete, the function accept()
		 * wakes up and returns the socket descriptor representing the client socket.
		 */
		int connfd = accept(sock, address, &address_size);

		sleep(1);
	}
}

#endif //__linux__