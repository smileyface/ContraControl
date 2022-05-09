#include "network_utiliies.h"

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

SOCKET test_sock;

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
	//test_sock = socket(maker.sock_family, maker.sock_type, maker.ip_protocol);
}