#include <string>

#include "Network/system_interfaces/network_interface.h"
#ifdef _WIN32
#include "Network/system_interfaces/windows_network_interface.h"
#endif
#ifdef __linux__
#include "Network/system_interfaces/linux_network_interface.h"
#endif

/*This is where the Network Interface object is defined */
Network_Interface* network::network_interface;


void Network_Interface::set_client()
{
	is_server = false;
}

void Network_Interface::set_server()
{
	is_server = true;
}

Network_Status_State Network_Interface::get_status()
{
	return status_state;
}


void network::init_network_interfaces()
{
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



