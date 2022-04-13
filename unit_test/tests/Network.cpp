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

#define ARRAY_LENGTH(array) (sizeof(array)/sizeof((array)[0]))

namespace {
	class LocalNetworkTest : public ::testing::Test {
		virtual void SetUp() {
			system_utilities::network_utilities::setup();
		}
		virtual void TearDown() {
			network::teardown_network_interfaces();
			system_utilities::cleanup();
		}
	};
	class EmptyLocalNetworkTest : public ::testing::Test {
		virtual void SetUp() {
			system_utilities::setup_messaging();
		}
		virtual void TearDown() {
			network::teardown_network_interfaces();
			system_utilities::cleanup();
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
	catch (const std::exception& exc)
	{
		std::cerr << exc.what();
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

