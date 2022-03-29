#include "../test_utilities/system_testings.h"
#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"

#include "../../Network/network_main.h"
#include "../../Network/messages.h"
namespace {
	class NetworkMessagingTest : public ::testing::Test {

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

TEST_F(NetworkMessagingTest, Message_NODE_HELLO)
{
	ipv4_addr address("192.168.86.3");
	std::string node_name = "Test_Node";
	Node_Messages::NODE_HELLO message(address.get_addr_bytes(), node_name.c_str());
	PACKED_MESSAGE p_message(&message);
	EXPECT_EQ(0, p_message.get_packet()[1]);
	EXPECT_EQ(p_message.get_packet().size(), p_message.get_packet()[2]);
}

TEST_F(NetworkMessagingTest, Message_NODE_ACK)
{
	std::string node_name = "Test_Node";
	Node_Messages::NODE_ACK message(true, node_name.c_str());
	PACKED_MESSAGE p_message(&message);
	EXPECT_EQ(1, p_message.get_packet()[1]);
	EXPECT_EQ(p_message.get_packet().size(), p_message.get_packet()[2]);
}

TEST_F(NetworkMessagingTest, Message_NODE_UNDEF)
{
	Node_Messages::NODE_CONNECT message;
	PACKED_MESSAGE p_message(&message);
	EXPECT_EQ(255, p_message.get_packet()[1]);
	EXPECT_EQ(p_message.get_packet().size(), p_message.get_packet()[2]);
}