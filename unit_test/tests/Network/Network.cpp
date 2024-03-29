#include "../../test_utilities/system_utilities.h"
#include "../../test_utilities/test_utilities.h"

#include "../../test_utilities/pch.h"

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

namespace {
	class Local_Network_Test : public ::testing::Test {
		virtual void SetUp() {
			system_utilities::setup();
			system_utilities::network_utilities::setup();
		}
		virtual void TearDown() {
			network::clean_up();
			system_utilities::cleanup();
		}
	};
}
TEST_F(Local_Network_Test, Network_SetUp)
{
	/** Start in server mode */
	testing_utilities::network_utilities::check_initalized();
	EXPECT_TRUE(network::network_interface->server());
}

TEST_F(Local_Network_Test, Server_Start_Up)
{
	/** Start in server mode */
	try
	{
		testing_utilities::network_utilities::check_initalized();
		network::start_server();
		EXPECT_TRUE(network::network_interface->server());
	}
	catch (NetworkErrorException e)
	{
		LOG_ERROR("Server Start Up exception caught", "Test");
		testing_utilities::network_utilities::exception_handle();
	}
	catch (const std::exception& exc)
	{
		std::cerr << exc.what();
	}
}


