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
	try
	{
		network::start_server();
	}
	catch (NetworkErrorException e)
	{
		testing_util::network_utilities::exception_handle(e);
	}
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
		testing_util::network_utilities::exception_handle(e);
	}
}