#include "../test_utilities/device_utilities.h"
#include "../test_utilities/system_testings.h"
#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"

#include "Network/system_interfaces/network_interface.h"

namespace {
	class NetworkTest : public ::testing::Test {
		virtual void SetUp() {
			system_util::setup();
			network::init_network_interfaces();
		}
		virtual void TearDown() {
			system_util::cleanup();
			network::teardown_network_interfaces();
		}

	};
}
TEST_F(NetworkTest, Network_SetUp)
{
	/** Start in server mode */
	testing_util::network_utilities::check_initalized();
}

TEST_F(NetworkTest, Server_Start_Up)
{
	/** Start in server mode */
	testing_util::network_utilities::check_initalized();
	network::start_server();
}

TEST_F(NetworkTest, Client_Start_Up)
{
	/** Start in server mode */
	testing_util::network_utilities::check_initalized();
	try 
	{
		network::start_client();
	}
	catch (NetworkErrorException e)
	{
		switch (network::network_interface->get_status().error)
		{
		case NETWORK_ERRORS::SOCKET_INVALID:
			FAIL() << "Invalid Socket";
			break;
		default:
			FAIL() << "Unknown Error";
		}
	}
}