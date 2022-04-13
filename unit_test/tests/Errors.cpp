#include "../test_utilities/system_testings.h"
#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"

#include "../../Network/network_main.h"
#ifdef _WIN32
#include "../../Network/system_interfaces/windows_network_interface.h"
#endif // _WIN32
#ifdef __linux__
#include "../../Network/system_interfaces/linux_network_interface.h"
#endif

namespace {
	class EmptyLocalNetworkTest : public ::testing::Test {
		virtual void SetUp() {
			system_utilities::setup_messaging();
		}
		virtual void TearDown() {
			system_utilities::cleanup();
		}

	};
}

/** System Specific interfaces */
#ifdef _WIN32
TEST_F(EmptyLocalNetworkTest, Error_States_Initialize_System_Interface_Error)
{
	testing_utilities::network_utilities::expect_exception([]() {network::network_interface->initalized(); }, NETWORK_ERRORS::SOCKET_INVALID);
	wVersionRequested = MAKEWORD(0, 0);
	testing_utilities::network_utilities::expect_exception([]() {network::init_network_interfaces(); }, NETWORK_ERRORS::SYSTEM_INTERFACE_ERROR);
	wVersionRequested = MAKEWORD(2, 2);
}
#endif


TEST_F(EmptyLocalNetworkTest, Error_States_Initalized)
{
	system_utilities::network_utilities::setup();
	network::network_interface->set_hostname(INVALID_HOSTNAME);
	testing_utilities::network_utilities::expect_exception([]() {network::network_interface->initalized(); }, NETWORK_ERRORS::INVALID_HOSTNAME);

	system_utilities::network_utilities::setup();
	network::network_interface->setup_connection(local_connections::local, { IPPROTO_MAX, SOCK_STREAM, AF_INET });
	testing_utilities::network_utilities::expect_exception([]() {network::network_interface->initalized(); }, NETWORK_ERRORS::SOCKET_INVALID);
}

TEST_F(EmptyLocalNetworkTest, Error_States_Broadcast_Setup)
{
#ifdef _WIN32
	testing_utilities::network_utilities::expect_exception([]() {network::network_interface->setup_connection(local_connections::broadcast, { IPPROTO_MAX, SOCK_STREAM, AF_INET }); }, NETWORK_ERRORS::SOCKET_INVALID);
#endif // !_WIN32
	system_utilities::network_utilities::setup();
	testing_utilities::network_utilities::expect_exception([]() {network::network_interface->setup_connection(local_connections::broadcast, { IPPROTO_MAX, SOCK_STREAM, AF_INET }); }, NETWORK_ERRORS::SOCKET_INVALID);
#ifdef _WIN32
	testing_utilities::network_utilities::expect_exception([]() {network::network_interface->setup_connection(local_connections::broadcast, { IPPROTO_TCP, SOCK_STREAM, AF_INET }); }, NETWORK_ERRORS::NETWORK_OPTION_ERROR);
#endif // !_WIN32
}
/*
TEST_F(EmptyLocalNetworkTest, Error_States_Local_Setup)
{
#ifdef _WIN32
#endif // !_WIN32
}
*/