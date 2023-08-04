#include "../../test_utilities/test_utilities.h"
#include "../../test_utilities/system_utilities.h"

#include "../../test_utilities/pch.h"

#include "../../dev/Interfaces/Messaging/message_relay.h"
#include "../../dev/View/view_main.h"

#include <sstream>
#include <stdio.h>



namespace
{
	class Command_View_Message_Test : public ::testing::Test
	{
	public:
		Message_Consumer* logging_messages;
		Message_Consumer* option_consumer;
		bool found = false;
		View_Handle display_handle = 0;
		virtual void SetUp()
		{
			system_utilities::setup();
			system_utilities::start_system();
			display_handle = view::add_display(DISPLAY_TYPES::CONSOLE);
			logging_messages = Message_Relay::get_instance()->register_consumer<Logging_Message>();
			option_consumer = Message_Relay::get_instance()->register_consumer<Option_Popup_Message>();
		}
		virtual void TearDown()
		{
			Message_Relay::get_instance()->deregister_consumer(logging_messages);
			Message_Relay::get_instance()->deregister_consumer(option_consumer);
			view::remove_display(display_handle);
			system_utilities::stop_system();
			system_utilities::cleanup();
		}
	};
}

TEST_F(Command_View_Message_Test, Request_Message_On_Relay)
{
	Message_Relay::get_instance()->push(new Option_Popup_Message(SUBSYSTEM_ID_ENUM::TEST, "Tester", { "Hello", "It's", "Me" }));
	EXPECT_FALSE(found);
	system_utilities::step(1);
	Option_Popup_Message opm = Message_Relay::get_instance()->pop<Option_Popup_Message>(option_consumer);
	EXPECT_FALSE(found);
	EXPECT_EQ(opm.get_sender(), SUBSYSTEM_ID_ENUM::TEST);
	Option_List list = opm.get_options();
	EXPECT_EQ(list[0], "Hello");
	EXPECT_EQ(list[1], "It's");
	EXPECT_EQ(list[2], "Me");
}

TEST_F(Command_View_Message_Test, Send_Option)
{
	Message_Relay::get_instance()->push(new Option_Popup_Message(SUBSYSTEM_ID_ENUM::TEST, "Tester", { "Hello", "It's", "Me" }));
	system_utilities::step(1);
	system_utilities::keyboard_utilities::Keyboard keyboard;
	//NEED TO ADD BUFFER INPUT INTERFACE
	keyboard < KEY::NUM_0;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	bool message_in_view = false;
	for(auto item = Message_Relay::get_instance()->pop(logging_messages); item != 0; item = Message_Relay::get_instance()->pop(logging_messages))
	{
		auto item_ref = item.convert_type<Logging_Message>();
		if(item_ref.get_priority() == MESSAGE_PRIORITY::INFO_MESSAGE &&
		   item_ref.get_location() == "Option Popup Creation" &&
		   item_ref.get_message() == "Option Popup request recieved from subsystem ID" + std::to_string(static_cast<int>(SUBSYSTEM_ID_ENUM::TEST)))
		{
			message_in_view = true;
		}
	}
	EXPECT_EQ(message_in_view, true);



}