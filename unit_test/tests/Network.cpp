#include "../test_utilities/system_testings.h"
#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"

#include "../../Network/network_main.h"
#ifdef _WIN32
#endif // _WIN32



namespace {
	class LocalNetworkTest : public ::testing::Test {
		virtual void SetUp() {
			try
			{
				system_utilities::setup();
				network::init_network_interfaces();
			}
			catch (NetworkErrorException e)
			{
				testing_utilities::network_utilities::exception_handle();
			}
		}
		virtual void TearDown() {
			system_utilities::cleanup();
			network::teardown_network_interfaces();
		}

	};
}
namespace {
	class EmptyLocalNetworkTest : public ::testing::Test {
		virtual void SetUp() {

		}
		virtual void TearDown() {

		}

	};
}
TEST_F(LocalNetworkTest, Network_SetUp)
{
	/** Start in server mode */
	testing_utilities::network_utilities::check_initalized();
}

TEST_F(LocalNetworkTest, Server_Start_Up)
{
	/** Start in server mode */
	try
	{
		testing_utilities::network_utilities::check_initalized();
		network::start_server();
	}
	catch (NetworkErrorException e)
	{
		std::cout << "Server Start Up exception caught";
		testing_utilities::network_utilities::exception_handle();
	}
}

TEST_F(LocalNetworkTest, Client_Start_Up)
{
	/** Start in server mode */	
	try
	{
		testing_utilities::network_utilities::check_initalized();
		network::start_client();
	}
	catch (NetworkErrorException e)
	{
		testing_utilities::network_utilities::exception_handle();
	}
}

/** System Specific interfaces */
#ifdef _WIN32
#include "../../Network/system_interfaces/windows_network_interface.h"
TEST_F(EmptyLocalNetworkTest, Error_States_Initialize_System_Interface_Error)
{
	testing_utilities::network_utilities::expect_exception([]() {network::network_interface->initalized(); }, NETWORK_ERRORS::SOCKET_INVALID);
	wVersionRequested = MAKEWORD(0, 0);
	testing_utilities::network_utilities::expect_exception(network::init_network_interfaces, NETWORK_ERRORS::SYSTEM_INTERFACE_ERROR);
}

TEST_F(EmptyLocalNetworkTest, Error_States_Initalized)
{
	wVersionRequested = MAKEWORD(2, 2);
	network::init_network_interfaces();
	network::network_interface->set_hostname(invalid_hostname);
	testing_utilities::network_utilities::expect_exception([]() {network::network_interface->initalized(); }, NETWORK_ERRORS::INVALID_HOSTNAME);

	network::init_network_interfaces();
	network::network_interface->setup_connection(local_connections::local, { IPPROTO_MAX, SOCK_STREAM, AF_INET });
	testing_utilities::network_utilities::expect_exception([]() {network::network_interface->initalized(); }, NETWORK_ERRORS::SOCKET_INVALID);
}

TEST_F(EmptyLocalNetworkTest, Error_States_Broadcast_Setup)
{
	testing_utilities::network_utilities::expect_exception([]() {network::network_interface->setup_connection(local_connections::broadcast, { IPPROTO_MAX, SOCK_STREAM, AF_INET }); }, NETWORK_ERRORS::SOCKET_INVALID);
	network::init_network_interfaces();
	testing_utilities::network_utilities::expect_exception([]() {network::network_interface->setup_connection(local_connections::broadcast, { IPPROTO_MAX, SOCK_STREAM, AF_INET }); }, NETWORK_ERRORS::SOCKET_INVALID);
	testing_utilities::network_utilities::expect_exception([]() {network::network_interface->setup_connection(local_connections::broadcast, { IPPROTO_TCP, SOCK_STREAM, AF_INET }); }, NETWORK_ERRORS::NETWORK_OPTION_ERROR);
}

TEST_F(EmptyLocalNetworkTest, Error_States_Local_Setup)
{
	network::network_interface->set_hostname(invalid_hostname);
	testing_utilities::network_utilities::expect_exception([]() {network::network_interface->setup_connection(local_connections::local, { IPPROTO_TCP, SOCK_STREAM, AF_INET }); }, NETWORK_ERRORS::INVALID_HOSTNAME);
}
#endif

#ifdef __linux__
TEST_F(EmptyLocalNetworkTest, Error_States_Linux)
{
}
#endif