#include <thread>
#include <mutex>

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
}

void client_loop()
{
	while (network_running)
	{

	}
}

void server_loop()
{
	while (network_running)
	{

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