#include "../test_utilities/system_testings.h"
#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"

#include <cstdlib>
#include <iostream>

#include "../../Network/network_main.h"
#include "../../Network/messages.h"
namespace {
	class NetworkMessagingCreationTest : public ::testing::Test {

		virtual void SetUp() {
			try
			{
				system_utilities::setup();
				if (std::getenv("CI") != NULL)
				{
					system_utilities::testing_messges->push(System_Message(MESSAGE_PRIORITY::INFO_MESSAGE, "On a CI machine", "Test Setup"));
					network::init_network_interfaces("nat");
				}
				else
				{
					system_utilities::testing_messges->push(System_Message(MESSAGE_PRIORITY::INFO_MESSAGE, "Not on a CI machine", "Test Setup"));
					network::init_network_interfaces();
				}
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

TEST_F(NetworkMessagingCreationTest, Message_Type)
{
	ipv4_addr address;
	std::string node_name = "Test_Node";
	MESSAGE message = node_messages::Network_Message_Factory(MESSAGES::UNDEFINED);
	message[0] = node_name;
	message[1] = address;
	message[2] = true;
	message[3] = Byte(100);
	message[4] = 12.01f;
	message[5] = -100;
	PACKED_MESSAGE p_message(message);
	testing_utilities::network_utilities::network_message_utilities::check_header(255, p_message.get_packet().size(), p_message.get_packet());
	PACKED_MESSAGE b_message(p_message.get_packet());
	testing_utilities::network_utilities::network_message_utilities::compare_messages(p_message, b_message);
}

TEST_F(NetworkMessagingCreationTest, Message_NODE_HELLO)
{
	ipv4_addr address("127.0.0.1");
	std::string node_name = "Test_Node";
	MESSAGE message = node_messages::Network_Message_Factory(MESSAGES::NODE_HELLO);
	message[0] = address;
	message[1] = node_name;
	PACKED_MESSAGE p_message(message);
	testing_utilities::network_utilities::network_message_utilities::check_header(0, p_message.get_packet().size(), p_message.get_packet());
	PACKED_MESSAGE b_message(p_message.get_packet());
	testing_utilities::network_utilities::network_message_utilities::compare_messages(p_message, b_message);
}

TEST_F(NetworkMessagingCreationTest, Message_NODE_ACK)
{
	std::string node_name = "Test_Node";
	MESSAGE message = node_messages::Network_Message_Factory(MESSAGES::NODE_ACK);
	message[0] = node_name;
	PACKED_MESSAGE p_message(message);
	testing_utilities::network_utilities::network_message_utilities::check_header(1, p_message.get_packet().size(), p_message.get_packet());
	PACKED_MESSAGE b_message(p_message.get_packet());
	testing_utilities::network_utilities::network_message_utilities::compare_messages(p_message, b_message);
}

TEST_F(NetworkMessagingCreationTest, Message_NODE_UNDEF)
{

}