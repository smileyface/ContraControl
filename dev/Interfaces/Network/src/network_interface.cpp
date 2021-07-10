#include <string>
#include <stdlib.h>     /* atof */
#include <vector>

#include "../Utilities/Utilities/system.h"

#include "Network/system_interfaces/network_interface.h"
#ifdef IS_WIN32
#include "Network/system_interfaces/windows_network_interface.h"
#endif
#ifdef IS_UNIX
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

ipv4_addr::ipv4_addr(char* str)
{
	size_t pos = 0;
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
#ifdef IS_WIN32
	network::network_interface = new Windows_Network_Interface();
#endif // IS_WIN32
#ifdef IS_UNIX
	network::network_interface = new Linux_Network_Interface();
#endif //IS_UNIX

	network_is_init = true;
}

/*This is where the Windows Network Interface object is defined*/
#ifdef IS_WIN32
void Windows_Network_Interface::connect(ipv4_addr addr)
{

}
#endif // IS_WIN32

/*This is where the Linux Network Interface object is defined*/
#ifdef IS_UNIX

#endif //IS_UNIX