#include "../test_utilities/system_utilities.h"
#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"

#include "../../dev/Interfaces/Messaging/message_relay.h"

namespace
{
	class Message_Pointer_Wrapper_Test : public ::testing::Test
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

TEST_F(Message_Pointer_Wrapper_Test, Create_Message_Wrapper)
{
	Message_Ptr<Logging_Message> mp(new Logging_Message());
	EXPECT_EQ(mp.count(), 1);
}

TEST_F(Message_Pointer_Wrapper_Test, Copy_Constructor)
{
	Message_Ptr<Logging_Message> mp(new Logging_Message());
	Message_Ptr<Logging_Message> mp2(mp);
	EXPECT_EQ(mp.count(), 2);
	EXPECT_EQ(mp2.count(), 2);

}

TEST_F(Message_Pointer_Wrapper_Test, Convert_Type)
{
	Message_Ptr<Internal_Message> mp(new Logging_Message(MESSAGE_PRIORITY::DEBUG_MESSAGE, "This is", "the one"));

	Logging_Message logging = mp.convert_type<Logging_Message>();
	EXPECT_EQ(logging.get_priority(), MESSAGE_PRIORITY::DEBUG_MESSAGE);
	EXPECT_EQ(logging.get_message(), "This is");
	EXPECT_EQ(logging.get_location(), "the one");
}