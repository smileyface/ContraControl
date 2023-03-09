#include "../test_utilities/system_utilities.h"
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
	class Network_Error_Test : public ::testing::Test {
		virtual void SetUp() {
			network::make_os_network_interface();
			system_utilities::setup_messaging();
		}
		virtual void TearDown() {
			system_utilities::cleanup();
		}

	};
}

/** System Specific interfaces */
#ifdef _WIN32
TEST_F(Network_Error_Test, Error_States_Initialize_System_Interface_Error)
{
	testing_utilities::network_utilities::expect_exception([]() {network::network_interface->initalized(); }, NETWORK_ERRORS::SOCKET_INVALID);
	wVersionRequested = MAKEWORD(0, 0);
	testing_utilities::network_utilities::expect_exception([]() {network::init_network_interfaces(); }, NETWORK_ERRORS::SYSTEM_INTERFACE_ERROR);
	wVersionRequested = MAKEWORD(2, 2);
}
#endif


TEST_F(Network_Error_Test, Error_States_Initalized)
{
	system_utilities::network_utilities::setup();
	network::network_interface->set_hostname(INVALID_HOSTNAME);
	testing_utilities::network_utilities::expect_exception([]() {network::network_interface->initalized(); }, NETWORK_ERRORS::INVALID_HOSTNAME);
	system_utilities::network_utilities::setup();
	network::network_interface->setup_connection(local_connections::local, { IPPROTO_MAX, SOCK_STREAM, AF_INET });
	testing_utilities::network_utilities::expect_exception([]() {network::network_interface->initalized(); }, NETWORK_ERRORS::SOCKET_INVALID);
}

TEST_F(Network_Error_Test, Error_States_Broadcast_Setup)
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

TEST_F(Network_Error_Test, Messaging_Types_Unimplemented)
{

	Network_Message message = node_messages::network_message_factory(MESSAGES::NODE_HELLO);
	testing_utilities::error_utilities::check_override_failure ([message]()mutable {message[0] = -110; });
	testing_utilities::error_utilities::check_override_failure([message]()mutable {message[0] = std::string("hi"); });
	testing_utilities::error_utilities::check_override_failure([message]()mutable {message[0] = Byte(32); });
	testing_utilities::error_utilities::check_override_failure([message]()mutable {message[0] = 33.92f; });
	testing_utilities::error_utilities::check_override_failure([message]()mutable {message[0] = true; });
	testing_utilities::error_utilities::check_override_failure([message]()mutable {message[1] = IPV4_Addr(); });
}

TEST_F(Network_Error_Test, Unfound_Address)
{
	testing_utilities::network_utilities::expect_exception([]() { network::init_network_interfaces("errors"); }, NETWORK_ERRORS::ADDRESS_ERROR);

#ifdef _WIN32
	network::set_interface("Loopback Pseudo-Interface 1");
#endif // _WIN32
#ifdef __linux__
	network::set_interface("lo");
#endif
}
