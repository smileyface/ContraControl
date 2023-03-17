#include "../../test_utilities/system_utilities.h"
#include "../../test_utilities/test_utilities.h"

#include "../../test_utilities/pch.h"

#include "../../dev/Interfaces/Messaging/message_relay.h"

namespace
{
	class Logging_Messages_Test : public ::testing::Test
	{
	public:
		Message_Consumer* consumer = 0;
		bool found = false;
		virtual void SetUp()
		{
			system_utilities::setup();
			if(consumer == 0)
				consumer = Message_Relay::get_instance()->register_consumer<Logging_Message>();
		}
		virtual void TearDown()
		{
			Message_Relay::get_instance()->deregister_consumer(consumer);
			system_utilities::cleanup();
		}
	};
}

TEST_F(Logging_Messages_Test, Logging_Levels_Test)
{
	LOG_DEBUG("Test Debug");
	Logging_Message message = Message_Relay::get_instance()->pop(consumer).convert_type<Logging_Message>();
	EXPECT_EQ(message.get_priority_string(), "DEBUG");
	LOG_ERROR("Test Error", "Test script");
	message = Message_Relay::get_instance()->pop(consumer).convert_type<Logging_Message>();
	EXPECT_EQ(message.get_priority_string(), "ERROR");
	LOG_INFO("Test Info", "Test Script");
	message = Message_Relay::get_instance()->pop(consumer).convert_type<Logging_Message>();
	EXPECT_EQ(message.get_priority_string(), "INFO");
	Message_Relay::get_instance()->push(new Logging_Message(MESSAGE_PRIORITY::SEVERE_MESSAGE, "Test Kaboom", "Test Script"));
	message = Message_Relay::get_instance()->pop(consumer).convert_type<Logging_Message>();
	EXPECT_EQ(message.get_priority_string(), "SEVERE");
	Message_Relay::get_instance()->push(new Logging_Message(MESSAGE_PRIORITY(255), "Test Kaboom", "Test Script"));
	message = Message_Relay::get_instance()->pop(consumer).convert_type<Logging_Message>();
	EXPECT_EQ(message.get_priority_string(), "UNHANDLED PRIORITY");
}
