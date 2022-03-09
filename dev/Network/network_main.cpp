#include "network_main.h"
#ifdef _WIN32
#include "system_interfaces/windows_network_interface.h"
#endif
#ifdef __linux__
#include "system_interfaces/linux_network_interface.h"
#endif

/*This is where the Network Interface object is defined */
Network_Interface* network::network_interface;
System_Messages* network::network_message_interface;

void network::init_network_interfaces()
{
	//network_message_interface = System_Messages::get_instance();
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

void network::teardown_network_interfaces()
{
	if (network::network_interface != nullptr)
	{
		network::network_interface->clean_up();
	}
}

void network::start_server()
{
	network::network_interface->set_server();
	network::network_interface->server_start();
}

void network::start_client()
{
	network::network_interface->set_client();
	network::network_interface->scan_for_server();
}