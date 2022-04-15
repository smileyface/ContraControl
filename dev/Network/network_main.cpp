#include <thread>
#include <mutex>

#include "messages.h"

#include "network_main.h"
#ifdef _WIN32
#include "system_interfaces/windows_network_interface.h"
#endif
#ifdef __linux__
#include "system_interfaces/linux_network_interface.h"
#endif

/*Externs*/
Network_Interface* network::network_interface;
System_Messages* network::network_message_interface;


bool network_running = false;
std::thread network_thread;
std::mutex network_mutex;

void network::init_network_interfaces()
{
	network_message_interface = System_Messages::get_instance();
#ifdef _WIN32
	network::network_interface = new Windows_Network_Interface();
#endif // IS_WIN32
#ifdef __linux__
	network::network_interface = new Linux_Network_Interface();
#endif //__linux__
#ifdef _MAC
	//For now, we'll just use the linux interface. 
	network::network_interface = new Linux_Network_Interface();
#endif // _MAC
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
	//call_and_response(NODE_HELLO, NODE_ACK, 2);
	while (network_running)
	{

	}
}

void server_loop()
{
	while (network_running)
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
	if (network::network_interface != nullptr)
	{
		network::network_interface->clean_up();
	}
	network::network_message_interface->push(System_Message(MESSAGE_PRIORITY::INFO_MESSAGE, "Network interface torndown", "Network Interfaces Teardown"));
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
}
