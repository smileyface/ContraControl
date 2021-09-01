/*This is where the Linux Network Interface object is defined*/
#ifdef __linux__


#include "Network/system_interfaces/linux_network_interface.h"
#include "../Utilities/Utilities/exceptions.h"

void Linux_Network_Interface::connect_to_server(ipv4_addr addr)
{
	throw UnimplementedFunctionException();
}

void Linux_Network_Interface::initalize()
{
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = DEFAULT_PORT;

	/* creates an UN-named socket inside the kernel and returns
	* an integer known as socket descriptor
	* This function takes domain/family as its first argument.
	* For Internet family of IPv4 addresses we use AF_INET
	*/
	listenfd = socket(sock_family, sock_type, ip_protocol);
	memset(&serv_addr, '0', sizeof(serv_addr));


	/* The call to the function "bind()" assigns the details specified
	 * in the structure 『serv_addr' to the socket created in the step above
	 */
	bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

	server_running = false;
}

void Linux_Network_Interface::clean_up()
{
	server_running = false;
	close(listenfd);
}

void Linux_Network_Interface::scan_for_server()
{
	throw UnimplementedFunctionException();
}

void Linux_Network_Interface::initalized()
{
	if (listenfd > 0)
	{
		status_state.set_error(NETWORK_ERRORS::SOCKET_INVALID);
	}
	status_state.set_status(NETWORK_STATUS::NETWORK_INITALIZED);
}

void Linux_Network_Interface::server_start()
{
	server_running = true;

}

void Linux_Network_Interface::server_listen()
{
	/* The call to the function "listen()" with second argument as 10 specifies
	 * maximum number of client connections that server will queue for this listening
	 * socket.
	 */
		listen(listenfd, 10);


	while (server_running)
	{
		/* In the call to accept(), the server is put to sleep and when for an incoming
		 * client request, the three way TCP handshake* is complete, the function accept()
		 * wakes up and returns the socket descriptor representing the client socket.
		 */
		connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);

		sleep(1);
	}
}

#endif //__linux__