/*This is where the Linux Network Interface object is defined*/
#ifdef __linux__
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

void Linux_Network_Interface::connect_to_server(ipv4_addr addr)
{
	serv_addr.sin_addr.s_addr = inet_addr(addr.get_as_string().c_str());
	int result = connect(sock, (struct sockaddr*)&serv_addr.sin_addr, sizeof(serv_addr));
	if (result != 0)
	{
		switch (errno)
		{
		case EISCONN:
			status_state.set_error(NETWORK_ERRORS::SOCKET_BUSY);
			break;
			//This is only essential for using ipv6. So I'm ignoring.
		case EAFNOSUPPORT:
			break;
		default:
			status_state.set_error(NETWORK_ERRORS::UNKNOWN_ERROR);
		}
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
	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = sock_family;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = DEFAULT_PORT;
	/* The call to the function "bind()" assigns the details specified
	 * in the structure 『serv_addr' to the socket created in the step above
	 */
	int res = bind(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

	if (res == -1)
	{
		switch (errno)
		{

		}
	}


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
	/*THIS IS PROBABLY THE BEST WAY*/
	////get my interface id (wlan0 for now)
	//struct ifaddrs* interfaceArray = NULL;
	//void* tempAddrPtr = NULL;
	//int rc = 0, s;
	//char host[1025];
	//char addressOutputBuffer[INET_ADDRSTRLEN];
	//rc = getifaddrs(&interfaceArray);
	//for (auto current_address = interfaceArray; current_address != NULL; current_address = current_address->ifa_next)
	//{
	//	if (current_address->ifa_name == interfaces)
	//	{
	//		
	//		 tempAddrPtr = &((struct sockaddr_in*)current_address->ifa_addr)->sin_addr;
	//		 

	//		 s = getnameinfo(current_address->ifa_addr,
	//			 (serv_addr.sin_family == AF_INET) ? sizeof(struct sockaddr_in) :
	//			 sizeof(struct sockaddr_in6),
	//			 host, 1025,
	//			 NULL, 0, 0x02);
	//	}
	//}

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

std::vector<ipv4_addr> blast_arp()
{
	const char* cmd = "ip neigh show";
	std::array<char, 128> buffer;
	std::vector<ipv4_addr> result;
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
	if (!pipe) {
		throw std::runtime_error("popen() failed!");
	}
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
		if (explode(buffer.data(), ' ')[5].find("REACHABLE") != std::string::npos) 
		{
			result.emplace_back(explode(buffer.data(), ' ')[0]);
		}
	}
	return result;
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

std::vector<ipv4_addr> scan_for_possibilities(SOCKET sock, ipv4_addr my_addr, Network_Status_State& status_state)
{
 	ipv4_addr subnet_mask = get_subnet_mask(sock, my_addr, status_state);
	//ipv4_addr host_mask = ~subnet_mask.S_un.S_addr;
	ipv4_addr subnet = my_addr.S_un.S_addr & subnet_mask.S_un.S_addr;

	std::map<ipv4_addr, DWORD> addresses;
	std::vector<ipv4_addr> possibilities = blast_arp();
	
	std::vector<ipv4_addr> thing;
	for (int i = 0; i<possibilities.size(); i++)
	{
		ipv4_addr tester(possibilities[i].S_un.S_addr & subnet_mask.S_un.S_addr);
		if ((possibilities[i].S_un.S_addr & subnet_mask.S_un.S_addr) == subnet.S_un.S_addr)
		{
			thing.push_back(possibilities[i]);
		}
	}
	return thing;
}

void Linux_Network_Interface::scan_for_server()
{
	std::vector<ipv4_addr> possibilites = scan_for_possibilities(sock, host_ip, status_state);
	for (int i = 0; i < possibilites.size(); i++)
	{
		connect_to_server(possibilites[i]);
	}
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