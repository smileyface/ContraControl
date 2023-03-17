#include "../../test_utilities/test_utilities.h"
#include "../../test_utilities/system_utilities.h"

#include "../../test_utilities/pch.h"

#include "../../../dev/Interfaces/Messaging/message_relay.h"
#include "../../../dev/View/input_interface/keyboard_buffer_input.h"
#include "../../../dev/View/input_interface/action_layer/predefined_layer.h"
#include "../../../dev/View/view_main.h"

#include <sstream>
#include <stdio.h>



namespace
{
	class Option_Popup_View_Test : public ::testing::Test
	{
	public:
		Message_Consumer* logging_messages;
		virtual void SetUp()
		{
			system_utilities::setup();
			logging_messages = Message_Relay::get_instance()->register_consumer<Logging_Message>();
			view::start_view();
		}
		virtual void TearDown()
		{
			view::stop_view();
			Message_Relay::get_instance()->deregister_consumer(logging_messages);
			system_utilities::cleanup();
		}
	};
}

TEST_F(Option_Popup_View_Test, Create_Option)
{
	view::add_display(DISPLAY_TYPES::CONSOLE);
	Message_Relay::get_instance()->push(new Option_Popup_Message(SUBSYSTEM_ID_ENUM::TEST, "Tester", { "Hello", "It's", "Me" }));
	

	bool message_in_view = false;
	for(auto item = Message_Relay::get_instance()->pop<Logging_Message>(logging_messages); !item.is_valid(); item = Message_Relay::get_instance()->pop<Logging_Message>(logging_messages))
	{
		if(item.get_priority() == MESSAGE_PRIORITY::INFO_MESSAGE &&
		   item.get_location() == "Option Popup Creation" &&
		   item.get_message() == "Option Popup request recieved from subsystem ID" + std::to_string(static_cast<int>(SUBSYSTEM_ID_ENUM::TEST)))
		{
			message_in_view = true;
		}
	}
	EXPECT_EQ(message_in_view, true);
}

TEST_F(Option_Popup_View_Test, Select_Option)
{
	view::add_display(DISPLAY_TYPES::CONSOLE);

	Message_Relay::get_instance()->push(new Option_Popup_Message(SUBSYSTEM_ID_ENUM::TEST, "Tester", { "Hello", "It's", "Me" }));
	system_utilities::sleep_thread(100);
	system_utilities::keyboard_utilities::Keyboard keyboard = system_utilities::keyboard_utilities::create_test_keyboard();
	keyboard.get_interface()->action_stack.change_action_layers(Predefined_Action_Layer::SIMPLE_BUFFERED_INPUT_LAYER);

	//keyboard < KEY::NUM_1;
	//keyboard < KEY::ENTER;
	//keyboard.get_interface()->stop_listening();
}
