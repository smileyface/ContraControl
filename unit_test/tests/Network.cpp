#include "../test_utilities/system_utilities.h"
#include "../test_utilities/test_utilities.h"
#include "../test_utilities/network_utiliies.h"

#include "../test_utilities/pch.h"

#include <chrono>
#include <thread>

#include "../../Network/network_main.h"
#ifdef _WIN32
#include "../../Network/system_interfaces/windows_network_interface.h"
#endif // _WIN32
#ifdef __linux__
#include "../../Network/system_interfaces/linux_network_interface.h"
#endif

#define ARRAY_LENGTH(array) (sizeof(array)/sizeof((array)[0]))

namespace
{
	class Local_Network_Test : public ::testing::Test
	{
		virtual void SetUp()
		{
			system_utilities::setup();
			network_utilities::setup();
		}
		virtual void TearDown()
		{
			network::teardown_network_interfaces();
			system_utilities::cleanup();
		}
	};
}

TEST_F(Local_Network_Test, Network_SetUp)
{
	/** Start in server mode */
	testing_utilities::network_utilities::check_initalized();
}

TEST_F(Local_Network_Test, Server_Start_Up)
{
	/** Start in server mode */
	try
	{
		testing_utilities::network_utilities::check_initalized();
		network::start_server();
	}
	catch(NetworkErrorException e)
	{
		std::cout << "Server Start Up exception caught";
		testing_utilities::network_utilities::exception_handle();
	}
	catch(const std::exception& exc)
	{
		std::cerr << exc.what();
	}
}

TEST_F(Local_Network_Test, Client_Start_Up)
{
	/** Start in server mode */
	try
	{
		testing_utilities::network_utilities::check_initalized();
		network::start_client();
		std::this_thread::sleep_for(std::chrono::seconds(1));
		//TODO Add a localhost listener
	}
	catch(NetworkErrorException e)
	{
		testing_utilities::network_utilities::exception_handle();
	}
}

TEST_F(Local_Network_Test, Socket_Bind)
{
	try
	{
		network::network_interface->bind_connection(local_connections::local, { IPPROTO_TCP, SOCK_STREAM, AF_INET });
	}
	catch(NetworkErrorException e)
	{
		testing_utilities::network_utilities::exception_handle();
	}
}