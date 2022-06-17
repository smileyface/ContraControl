#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"

#include "../../dev/Interfaces/Messaging/message_relay.h"

namespace
{
	class Internal_Message_Test : public ::testing::Test
	{
	public:
		Message_Consumer* consumer;
		bool found;
		virtual void SetUp()
		{
			consumer = new Message_Consumer(found, new Logging_Message());
			Message_Relay::get_instance()->register_consumer(consumer);
		}
		virtual void TearDown()
		{
			Message_Relay::get_instance()->deregister_consumer(consumer);
		}
	};
}

TEST_F(Internal_Message_Test, Logging_Levels_Test)
{
	LOG_DEBUG("Test Debug");
	Logging_Message* message = dynamic_cast<Logging_Message*>(Message_Relay::get_instance()->pop(consumer));
	EXPECT_EQ(message->get_priority_string(), "DEBUG");
	LOG_ERROR("Test Error", "Test script");
	message = dynamic_cast<Logging_Message*>(Message_Relay::get_instance()->pop(consumer));
	EXPECT_EQ(message->get_priority_string(), "ERROR");
	LOG_INFO("Test Info", "Test Script");
	message = dynamic_cast<Logging_Message*>(Message_Relay::get_instance()->pop(consumer));
	EXPECT_EQ(message->get_priority_string(), "INFO");
	Message_Relay::get_instance()->push(new Logging_Message(MESSAGE_PRIORITY::SEVERE_MESSAGE, "Test Kaboom", "Test Script"));
	message = dynamic_cast<Logging_Message*>(Message_Relay::get_instance()->pop(consumer));
	EXPECT_EQ(message->get_priority_string(), "SEVERE");
}

TEST_F(Internal_Message_Test, Multiple_Consumer)
{
	Message_Consumer* con_two;
	con_two = new Message_Consumer(found, new Logging_Message());
	LOG_DEBUG("Test Debug");
	Message_Relay::get_instance()->register_consumer(con_two);
	Logging_Message* message = dynamic_cast<Logging_Message*>(Message_Relay::get_instance()->pop(con_two));
	EXPECT_EQ(message->get_message(), "Test Debug");
}