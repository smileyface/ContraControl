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

namespace
{
	class Client_Network_Test : public ::testing::Test
	{
		virtual void SetUp()
		{
			system_utilities::setup();
			system_utilities::network_utilities::setup();
		}
		virtual void TearDown()
		{
			network::clean_up();
			system_utilities::cleanup();
		}
	};
}

TEST_F(Client_Network_Test, Network_SetUp)
{
	/** Start in server mode */
	testing_utilities::network_utilities::check_initalized();
}