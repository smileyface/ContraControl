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
}