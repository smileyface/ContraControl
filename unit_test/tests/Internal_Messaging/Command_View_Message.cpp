#include "../../test_utilities/test_utilities.h"
#include "../../test_utilities/system_utilities.h"

#include "../../test_utilities/pch.h"

#include "../../dev/Interfaces/Messaging/message_relay.h"
#include "../../dev/View/input_interface/keyboard_buffer_input.h"
#include "../../dev/View/input_interface/action_layer/predefined_layer.h"
#include "../../dev/View/view_main.h"

#include <sstream>
#include <stdio.h>



namespace
{
	class Command_View_Message_Test : public ::testing::Test
	{
	public:
		Message_Consumer* logging_messages = 0;
		Message_Consumer* option_consumer = 0;
		bool found = false;
		virtual void SetUp()
		{

			system_utilities::setup();
			logging_messages = Message_Relay::get_instance()->register_consumer<Logging_Message>();
			option_consumer = Message_Relay::get_instance()->register_consumer<Option_Popup_Message>();

			view::start_view();
		}
		virtual void TearDown()
		{
			view::stop_view();
			Message_Relay::get_instance()->deregister_consumer(logging_messages);
			Message_Relay::get_instance()->deregister_consumer(option_consumer);
			system_utilities::cleanup();
		}
	};
}

TEST_F(Command_View_Message_Test, Send_Option)
{
	Message_Relay::get_instance()->push(new Option_Popup_Message(SUBSYSTEM_ID_ENUM::TEST, "Tester", { "Hello", "It's", "Me" }));
	EXPECT_FALSE(found);
	Option_Popup_Message opm = Message_Relay::get_instance()->pop<Option_Popup_Message>(option_consumer);
	EXPECT_FALSE(found);
	EXPECT_EQ(opm.get_sender(), SUBSYSTEM_ID_ENUM::TEST);
	Option_List list=opm.get_options();
	EXPECT_EQ(list[0], "Hello");
	EXPECT_EQ(list[1], "It's");
	EXPECT_EQ(list[2], "Me");
}
