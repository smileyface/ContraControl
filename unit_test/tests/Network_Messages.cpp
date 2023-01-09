#include "../test_utilities/system_utilities.h"
#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"

#include <cstdlib>
#include <iostream>

#include "../../Network/network_main.h"
#include "../../Network/messages.h"
namespace {
	class Network_Messaging_Test : public ::testing::Test {

		virtual void SetUp() {
			system_utilities::setup();
		}
		virtual void TearDown() {
			network::teardown_network_interfaces();
			system_utilities::cleanup();
		}
	};
}

TEST_F(Network_Messaging_Test, Message_Type)
{
	IPV4_Addr address;
	std::string node_name = "Test_Node";
	Network_Message message = node_messages::network_message_factory(MESSAGES::UNDEFINED);
	message[0] = node_name;
	message[1] = address;
	message[2] = true;
	message[3] = Byte(100);
	message[4] = 12.01f;
	message[5] = -100;
	Packed_Message p_message(message);
	testing_utilities::network_utilities::network_message_utilities::check_header(255, p_message.get_packet().size(), p_message.get_packet());
	Packed_Message b_message(p_message.get_packet());
	testing_utilities::network_utilities::network_message_utilities::compare_messages(p_message, b_message);
}

TEST_F(Network_Messaging_Test, Message_NODE_HELLO)
{
	IPV4_Addr address("127.0.0.1");
	std::string node_name = "Test_Node";
	Network_Message message = node_messages::network_message_factory(MESSAGES::NODE_HELLO);
	message[0] = address;
	message[1] = node_name;
	Packed_Message p_message(message);
	testing_utilities::network_utilities::network_message_utilities::check_header(0, p_message.get_packet().size(), p_message.get_packet());
	Packed_Message b_message(p_message.get_packet());
	testing_utilities::network_utilities::network_message_utilities::compare_messages(p_message, b_message);
}

TEST_F(Network_Messaging_Test, Message_NODE_ACK)
{
	std::string node_name = "Test_Node";
	Network_Message message = node_messages::network_message_factory(MESSAGES::NODE_ACK);
	message[0] = node_name;
	Packed_Message p_message(message);
	testing_utilities::network_utilities::network_message_utilities::check_header(1, p_message.get_packet().size(), p_message.get_packet());
	Packed_Message b_message(p_message.get_packet());
	testing_utilities::network_utilities::network_message_utilities::compare_messages(p_message, b_message);
}

TEST_F(Network_Messaging_Test, Message_NODE_UNDEF)
{

}