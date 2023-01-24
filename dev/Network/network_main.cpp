#include <thread>
#include <mutex>

#include "messages.h"
#include "messages/node_communication.h"

#include "network_main.h"
#ifdef _WIN32
#include "system_interfaces/windows_network_interface.h"
#endif
#ifdef __linux__
#include "system_interfaces/linux_network_interface.h"
#endif

/*Externs*/
#ifdef _WIN32
Network_Interface* network::network_interface = new Windows_Network_Interface();
#endif // IS_WIN32
#ifdef __linux__
Network_Interface* network::network_interface = new Linux_Network_Interface();
#endif //__linux__
#ifdef _MAC
//For now, we'll just use the linux interface.
Network_Interface* network::network_interface = new Linux_Network_Interface();
#endif // _MAC

bool network_running = false;
std::thread network_thread;
std::mutex network_mutex;

void network::init_network_interfaces()
{

	network_interface->initalize();
	generate_crc_table();
}

void network::init_network_interfaces(std::string interfaces)
{
	init_network_interfaces();
	network_interface->clean_up();
	network_interface->set_interface(interfaces);
	network_interface->initalize();
}

void client_loop()
{
	LOG_INFO("Starting Client Loop", "Client Loop");
	//call_and_response(NODE_HELLO, NODE_ACK, 2);
	while(network_running)
	{
		node_messages::network_client_state_machine();
	}
}

void server_loop()
{
	while(network_running)
	{
		//listen on Broadcast for NODE_HELLO
		//Once found, Send NODE_ACK
	}
}

void network::teardown_network_interfaces()
{
	network_running = false;
	if(network_thread.joinable())
		network_thread.join();
	if(network::network_interface != nullptr)
	{
		network::network_interface->clean_up();
	}
	LOG_INFO("Network Interface torndown", "Network");
}

Network_Message network::listen_for_message(Connection_Id src, MESSAGES listen_for)
{
	return Network_Message();
}

void network::start_server()
{
	network::network_interface->set_server();
	network_running = true;
	network_thread = std::thread(server_loop);
}

void network::start_client()
{
	network::network_interface->set_client();
	network_running = true;
	network_thread = std::thread(client_loop);
}

void network::set_interface(std::string i)
{
	network_interface->set_interface(i);
}

void network::send_message(Connection_Id dest, Network_Message outgoing)
{
	Packed_Message packed_outgoing(outgoing);
	network_interface->send(dest, reinterpret_cast<char*>(packed_outgoing.get_packet().data()));
	LOG_DEBUG("Sending message " + get_message_type_string(packed_outgoing.get_message_type()) + " to " + dest);
}