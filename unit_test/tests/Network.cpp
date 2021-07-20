#include "../test_utilities/device_utilities.h"
#include "../test_utilities/system_testings.h"
#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"

#include "Network/system_interfaces/network_interface.h"

namespace {
	class NetworkTest : public ::testing::Test {
		virtual void SetUp() {
			system_util::setup();
		}
		virtual void TearDown() {
			system_util::cleanup();
		}

	};
}
TEST_F(NetworkTest, Network_SetUp)
{
	/** Start in server mode */
	network::init_network_interfaces();
	EXPECT_EQ(network::network_interface->initalized(), true);
}