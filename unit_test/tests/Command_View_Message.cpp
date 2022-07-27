#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"

#include "../../dev/Interfaces/Messaging/message_relay.h"

namespace
{
	class Command_View_Message_Test : public ::testing::Test
	{
	public:
		Message_Consumer* logging_messages = new Message_Consumer(found, new Logging_Message());
		Message_Consumer* option_consumer = new Message_Consumer(found, new Option_Popup_Message());
		bool found = false;
		virtual void SetUp()
		{
			Message_Relay::get_instance()->register_consumer(logging_messages);
			Message_Relay::get_instance()->register_consumer(option_consumer);
		}
		virtual void TearDown()
		{
			Message_Relay::get_instance()->deregister_consumer(logging_messages);
			Message_Relay::get_instance()->deregister_consumer(option_consumer);
		}
	};
}

TEST_F(Command_View_Message_Test, Send_Option)
{
	Message_Relay::get_instance()->push(new Option_Popup_Message(SUBSYSTEM_ID_ENUM::VIEW, { "Hello", "It's", "Me" }));
	EXPECT_TRUE(found);
	Option_Popup_Message* opm = dynamic_cast<Option_Popup_Message*>(Message_Relay::get_instance()->pop(option_consumer));
	EXPECT_FALSE(found);
	EXPECT_EQ(opm->get_sender(), SUBSYSTEM_ID_ENUM::VIEW);
	Option_List list=opm->get_options();
	EXPECT_EQ(list[0], "Hello");
	EXPECT_EQ(list[1], "It's");
	EXPECT_EQ(list[2], "Me");
}