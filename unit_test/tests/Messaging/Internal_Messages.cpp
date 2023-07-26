#include "../../test_utilities/system_utilities.h"
#include "../../test_utilities/test_utilities.h"

#include "../../test_utilities/pch.h"

#include "../../dev/Interfaces/Messaging/message_relay.h"

namespace
{
	class Internal_Message_Test : public ::testing::Test
	{
	public:
		Message_Consumer* consumer = 0;
		bool found = false;
		virtual void SetUp()
		{
			system_utilities::setup();
			consumer = Message_Relay::get_instance()->register_consumer<Logging_Message>();
		}
		virtual void TearDown()
		{
			Message_Relay::get_instance()->deregister_consumer(consumer);
			system_utilities::cleanup();
		}
	};
}


TEST_F(Internal_Message_Test, Add_Message)
{
	EXPECT_EQ(Message_Relay::get_instance()->number_of_messages(consumer), 0);
	LOG_INFO("This is a new message", "Add message test");
	EXPECT_EQ(Message_Relay::get_instance()->number_of_messages(consumer), 1);
}
TEST_F(Internal_Message_Test, Logging_Levels_Test)
{
	LOG_DEBUG("Test Debug");
	Logging_Message message = Message_Relay::get_instance()->pop<Logging_Message>(consumer);
	EXPECT_EQ(message.get_priority_string(), "DEBUG");
	LOG_ERROR("Test Error", "Test script");
	message = Message_Relay::get_instance()->pop<Logging_Message>(consumer);
	EXPECT_EQ(message.get_priority_string(), "ERROR");
	LOG_INFO("Test Info", "Test Script");
	message = Message_Relay::get_instance()->pop<Logging_Message>(consumer);
	EXPECT_EQ(message.get_priority_string(), "INFO");
	Message_Relay::get_instance()->push(new Logging_Message(MESSAGE_PRIORITY::SEVERE_MESSAGE, "Test Kaboom", "Test Script"));
	message = Message_Relay::get_instance()->pop<Logging_Message>(consumer);
	EXPECT_EQ(message.get_priority_string(), "SEVERE");
	Message_Relay::get_instance()->push(new Logging_Message(MESSAGE_PRIORITY(255), "Test Kaboom", "Test Script"));
	message = Message_Relay::get_instance()->pop<Logging_Message>(consumer);
	EXPECT_EQ(message.get_priority_string(), "UNHANDLED PRIORITY");
}

TEST_F(Internal_Message_Test, Multiple_Consumer)
{
	Message_Consumer* con_two =
		Message_Relay::get_instance()->register_consumer<Logging_Message>();
	LOG_DEBUG("Test Debug");
	Logging_Message message = Message_Relay::get_instance()->pop<Logging_Message>(con_two);
	EXPECT_EQ(message.get_message(), "Test Debug");
	Message_Relay::get_instance()->deregister_consumer(con_two);
}

TEST_F(Internal_Message_Test, Freshen)
{
	EXPECT_FALSE(consumer->is_stale());
	LOG_DEBUG("Test Debug");
	EXPECT_TRUE(consumer->is_stale());
	Message_Relay::get_instance()->pop(consumer);
	EXPECT_FALSE(consumer->is_stale());
}
