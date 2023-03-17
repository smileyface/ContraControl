#include "../../test_utilities/system_utilities.h"
#include "../../test_utilities/test_utilities.h"

#include "../../test_utilities/pch.h"

#include "../../dev/Interfaces/Messaging/message_relay.h"

namespace
{
	class Message_Relay_Test : public ::testing::Test
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

TEST_F(Message_Relay_Test, Multiple_Consumer)
{
	//pop destroys a message, when it should destroy when 
	LOG_DEBUG("Test Debug");
	Message_Consumer* con_two = Message_Relay::get_instance()->register_consumer<Logging_Message>();
	Logging_Message message = Message_Relay::get_instance()->pop(con_two).convert_type<Logging_Message>();
	message.placeholder();
	EXPECT_EQ(message.get_message(), "Test Debug");

	Message_Relay::get_instance()->deregister_consumer(con_two);
}

TEST_F(Message_Relay_Test, Freshen)
{
	EXPECT_FALSE(consumer->is_stale());
	LOG_DEBUG("Test Debug");
	EXPECT_TRUE(consumer->is_stale());
	Message_Relay::get_instance()->pop(consumer);
	EXPECT_FALSE(consumer->is_stale());
}

TEST_F(Message_Relay_Test, Register_Consumer)
{
	LOG_DEBUG("Test Debug");
	Message_Consumer* con_two = Message_Relay::get_instance()->register_consumer<Logging_Message>();
	EXPECT_TRUE(Message_Relay::get_instance()->has_consumer(con_two));
	Message_Relay::get_instance()->deregister_consumer(con_two);
}

TEST_F(Message_Relay_Test, Deregister_Consumer)
{
	LOG_DEBUG("Test Debug");
	Message_Consumer* con_two = Message_Relay::get_instance()->register_consumer<Logging_Message>();
	EXPECT_TRUE(Message_Relay::get_instance()->has_consumer(con_two));
	Message_Relay::get_instance()->deregister_consumer(con_two);
	EXPECT_FALSE(Message_Relay::get_instance()->has_consumer(con_two));
	Message_Relay::get_instance()->deregister_consumer(con_two);
}

TEST_F(Message_Relay_Test, Consumer_Messages)
{
	Message_Consumer* con_two = Message_Relay::get_instance()->register_consumer<Logging_Message>();
	EXPECT_EQ(0, Message_Relay::get_instance()->number_of_messages(con_two));
	LOG_DEBUG("Test Debug");
	EXPECT_EQ(1, Message_Relay::get_instance()->number_of_messages(con_two));
	Message_Relay::get_instance()->deregister_consumer(con_two);
	con_two = Message_Relay::get_instance()->register_consumer<Logging_Message>();
	EXPECT_EQ(1, Message_Relay::get_instance()->number_of_messages(con_two));

	Message_Relay::get_instance()->deregister_consumer(con_two);
}