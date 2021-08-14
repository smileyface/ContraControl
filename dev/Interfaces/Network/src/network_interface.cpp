#include <string>
#include <vector>

#include "../Utilities/Utilities/system.h"

#include "Network/system_interfaces/network_interface.h"
#ifdef _WIN32
#include "Network/system_interfaces/windows_network_interface.h"
#endif
#ifdef __linux__
#include "Network/system_interfaces/linux_network_interface.h"
#endif

/*This is where the Network Interface object is defined */
Network_Interface* network::network_interface;

bool network_is_init = false;

void Network_Interface::set_client()
{
	is_server = false;
}

void Network_Interface::set_server()
{
	is_server = true;
}

unsigned char* Network_Interface::local_ip()
{
	return my_ip.get_addr_bytes();
}

ipv4_addr::ipv4_addr(char* str)
{
	size_t pos = 0;
	S_un = { 0,0,0,0 };
	std::string str_addr(str);
	std::vector<unsigned char> bytes;
	while ((pos = str_addr.find(".")) != std::string::npos) {
		char byte = atoi(str_addr.substr(0, pos).c_str());
		bytes.push_back(static_cast<unsigned char>(byte));
		str_addr.erase(0, pos + 1);
	}
	char byte = atoi(str_addr.c_str());
	bytes.push_back(static_cast<unsigned char>(byte));
	if (bytes.size() == 4)
	{
		S_un.S_un_b.s_b1 = bytes[0];
		S_un.S_un_b.s_b2 = bytes[1];
		S_un.S_un_b.s_b3 = bytes[2];
		S_un.S_un_b.s_b4 = bytes[3];
	}
}

void network::init_network_interfaces()
{
#ifdef _WIN32
	network::network_interface = new Windows_Network_Interface();
#endif // IS_WIN32
#ifdef __linux__
	network::network_interface = new Linux_Network_Interface();
#endif //__linux__
	network_interface->initalize();
	network_is_init = true;
}

void network::teardown_network_interfaces()
{
	network::network_interface->clean_up();
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



/*This is where the Linux Network Interface object is defined*/
#ifdef __linux__

void Linux_Network_Interface::connect_to_server(ipv4_addr addr)
{

}

void Linux_Network_Interface::initalize()
{

}

bool Linux_Network_Interface::initalized()
{
	return false;
}

#endif //__linux__