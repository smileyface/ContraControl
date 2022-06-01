#include "network_utiliies.h"

#include<iostream>

#include "system_utilities.h"
#include "test_utilities.h"

#include "Utilities/exceptions.h"

#include "../../Network/network_main.h"
#ifdef _WIN32
#include "../../Network/system_interfaces/windows_network_interface.h"
#endif // _WIN32
#ifdef __linux__
#include "../../Network/system_interfaces/linux_network_interface.h"
#endif

SOCKET network_utilities::test_broadcast_sock;
SOCKET network_utilities::test_direct_sock;

void errno_abort(const char* header)
{
#ifdef _WIN32
	std::cout << header << ": Error number " << WSAGetLastError();
#endif
#ifdef __linux__
	perror(header);
#endif
	exit(EXIT_FAILURE);
}

void network_utilities::setup()
{
	try
	{
		network::init_network_interfaces();
	}
	catch(NetworkErrorException e)
	{
		testing_utilities::network_utilities::exception_handle();
	}

	Socket_Maker maker = { IPPROTO_UDP, SOCK_DGRAM, AF_INET };
	test_broadcast_sock = socket(maker.sock_family, maker.sock_type, maker.ip_protocol);
	maker = { IPPROTO_TCP, SOCK_STREAM, AF_INET };
	test_direct_sock = socket(maker.sock_family, maker.sock_type, maker.ip_protocol);
	sockaddr_in clientService;
	clientService.sin_family = maker.sock_family;
	clientService.sin_port = htons(DEFAULT_PORT + 50);
#ifdef _WIN32
	char broadcast_opt_true = '1';
	setsockopt(test_broadcast_sock, SOL_SOCKET, SO_BROADCAST, (char*) &broadcast_opt_true, sizeof(broadcast_opt_true));
	char reuse_opt_true = '1';
	setsockopt(test_direct_sock, SOL_SOCKET, SO_REUSEADDR, &reuse_opt_true, sizeof(reuse_opt_true));
	clientService.sin_addr.S_un.S_addr = INADDR_ANY;
#endif // _WIN32
#ifdef __linux__
	int broadcast_opt_true = 1;
	setsockopt(test_broadcast_sock, SOL_SOCKET, SO_BROADCAST, &broadcast_opt_true, sizeof(broadcast_opt_true));
	int reuse_opt_true = 1;
	setsockopt(test_direct_sock, SOL_SOCKET, SO_REUSEADDR, &reuse_opt_true, sizeof(reuse_opt_true));
	clientService.sin_addr.s_addr = INADDR_ANY;
#endif

	int res = bind(test_broadcast_sock, (struct sockaddr*) &clientService, sizeof(clientService));
	if(res < 0)
	{
		errno_abort("Bind Broadcast");
	}
#ifdef _WIN32
	clientService.sin_addr.S_un.S_addr = INADDR_LOOPBACK;
#endif // _WIN32
#ifdef __linux__
	clientService.sin_addr.s_addr = INADDR_LOOPBACK;
#endif
	inet_pton(AF_INET, "127.0.0.1", &(clientService.sin_addr));
	setsockopt(test_direct_sock, SOL_SOCKET, SO_REUSEADDR, &reuse_opt_true, sizeof(reuse_opt_true));
	res = bind(test_direct_sock, (struct sockaddr*) &clientService, sizeof(clientService));
	if(res < 0)
	{
		errno_abort("Bind Direct Socket");
	}
}

void network_utilities::cleanup()
{
#ifdef _WIN32
	closesocket(test_direct_sock);
	closesocket(test_broadcast_sock);
#endif // _WIN32
#ifdef __linux__
	close(test_direct_sock);
	close(test_broadcast_sock);
#endif
	network::teardown_network_interfaces();
}

void network_utilities::send_broadcast_message(std::vector<char> message)
{
	struct sockaddr_in send_addr{};
	send_addr.sin_family = AF_INET;
	send_addr.sin_port = DEFAULT_PORT;
	// broadcasting address for unix (?)
#ifdef _WIN32
	send_addr.sin_addr.S_un.S_addr = inet_addr("127.255.255.255");
#endif // _WIN32
#ifdef __linux__
	send_addr.sin_addr.s_addr = inet_addr("255.255.255.255");
#endif
	int res = sendto(network_utilities::test_broadcast_sock, &message[0], message.size() + 1, 0,
					 (struct sockaddr*) &send_addr, sizeof send_addr);
	if(res < 0)
	{
		errno_abort("send");
	}
}
