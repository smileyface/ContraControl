#include "../test_utilities/system_testings.h"
#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"

#include "Network/system_interfaces/network_interface.h"

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