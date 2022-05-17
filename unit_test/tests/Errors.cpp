#include "../test_utilities/system_utilities.h"
#include "../test_utilities/test_utilities.h"
#include "../test_utilities/network_utiliies.h"

#include "../test_utilities/pch.h"

#include "../../Network/network_main.h"
#ifdef _WIN32
#include "../../Network/system_interfaces/windows_network_interface.h"
#endif // _WIN32
#ifdef __linux__
#include "../../Network/system_interfaces/linux_network_interface.h"
#endif

namespace
{
	class Network_Error_Test : public ::testing::Test
	{
		virtual void SetUp()
		{
			system_utilities::setup_messaging();
		}
		virtual void TearDown()
		{
			system_utilities::cleanup();
		}
	};
}

/** System Specific interfaces */
#ifdef _WIN32
TEST_F(Network_Error_Test, Error_States_Initialize_System_Interface_Error)
{
	testing_utilities::network_utilities::expect_exception([] ()
														   {
															   network::network_interface->setup_connection(local_connections::broadcast, { IPPROTO_MAX, SOCK_STREAM, AF_INET });
														   }, NETWORK_ERRORS::UNINITALIZED_INTERFACE);
	testing_utilities::network_utilities::expect_exception([] ()
														   {
															   network::network_interface->initalized();
														   }, NETWORK_ERRORS::SOCKET_INVALID);
	wVersionRequested = MAKEWORD(0, 0);
	testing_utilities::network_utilities::expect_exception([] ()
														   {
															   network::init_network_interfaces();
														   }, NETWORK_ERRORS::SYSTEM_INTERFACE_ERROR);
	wVersionRequested = MAKEWORD(2, 2);
}
#endif

TEST_F(Network_Error_Test, Error_States_Initalized)
{
	network_utilities::setup();
	network::network_interface->set_hostname(INVALID_HOSTNAME);
	testing_utilities::network_utilities::expect_exception([] ()
														   {
															   network::network_interface->initalized();
														   }, NETWORK_ERRORS::INVALID_HOSTNAME);
	network_utilities::cleanup();

	network_utilities::setup();
	testing_utilities::network_utilities::expect_exception([] ()
														   {
															   network::network_interface->setup_connection(local_connections::local, { IPPROTO_MAX, SOCK_STREAM, AF_INET });
														   }, NETWORK_ERRORS::NETWORK_OPTION_ERROR);

	network_utilities::cleanup();
}

TEST_F(Network_Error_Test, Error_States_Broadcast_Setup)
{
	network_utilities::setup();

/*	testing_utilities::network_utilities::expect_exception([] ()
														   {
															   network::network_interface->setup_connection(local_connections::broadcast, { IPPROTO_MAX, SOCK_STREAM, AF_INET });
														   }, NETWORK_ERRORS::SOCKET_INVALID);
	network_utilities::cleanup();

	network_utilities::setup();*/
#ifdef _WIN32
	testing_utilities::network_utilities::expect_exception([] ()
														   {
															   network::network_interface->setup_connection(local_connections::broadcast, { IPPROTO_TCP, SOCK_STREAM, AF_INET });
														   }, NETWORK_ERRORS::NETWORK_OPTION_ERROR);
#endif
	network_utilities::cleanup();
}
/*
TEST_F(EmptyLocalNetworkTest, Error_States_Local_Setup)
{
}
*/

TEST_F(Network_Error_Test, Messaging_Types_Unimplemented)
{
	Network_Message message = node_messages::network_message_factory(MESSAGES::NODE_HELLO);
	testing_utilities::error_utilities::check_override_failure([message] ()mutable
															   {
																   message[0] = -110;
															   });
	testing_utilities::error_utilities::check_override_failure([message] ()mutable
															   {
																   message[0] = std::string("hi");
															   });
	testing_utilities::error_utilities::check_override_failure([message] ()mutable
															   {
																   message[0] = Byte(32);
															   });
	testing_utilities::error_utilities::check_override_failure([message] ()mutable
															   {
																   message[0] = 33.92f;
															   });
	testing_utilities::error_utilities::check_override_failure([message] ()mutable
															   {
																   message[0] = true;
															   });
	testing_utilities::error_utilities::check_override_failure([message] ()mutable
															   {
																   message[1] = IPV4_Addr();
															   });
}

TEST_F(Network_Error_Test, Unfound_Address)
{
	network_utilities::setup();
	testing_utilities::network_utilities::expect_exception([] ()
														   {
															   network::init_network_interfaces("errors");
														   }, NETWORK_ERRORS::ADDRESS_ERROR);
	network_utilities::cleanup();
}
TEST_F(Network_Error_Test, Bind_To_Invalid_Address)
{
	network_utilities::setup();
	testing_utilities::network_utilities::expect_exception([] ()
														   {
															   IPV4_Addr test_address("255.0.255.0");
															   network::network_interface->setup_connection("Tester", { IPPROTO_TCP, SOCK_STREAM, AF_INET, test_address });
														   }, NETWORK_ERRORS::ADDRESS_ERROR);
	network_utilities::cleanup();
}