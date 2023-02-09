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
		Option_Popup_View_Test()
		{
			logging_messages = new Message_Consumer(new Logging_Message());
		}
		~Option_Popup_View_Test()
		{
			delete logging_messages;
		}
		virtual void SetUp()
		{
			system_utilities::setup();
			Message_Relay::get_instance()->register_consumer(logging_messages);
			view::initalize();
			view::start_view();
		}
		virtual void TearDown()
		{
			view::stop_view();
			view::remove_all();
			Message_Relay::get_instance()->deregister_consumer(logging_messages);
			system_utilities::cleanup();
		}
	};
}

TEST_F(Option_Popup_View_Test, Create_Option)
{
	view::add_display(DISPLAY_TYPES::CONSOLE);
	Message_Relay::get_instance()->push(new Option_Popup_Message(SUBSYSTEM_ID_ENUM::TEST, "Tester", { "Hello", "It's", "Me" }));
	

	system_utilities::sleep_thread(100);
	bool message_in_view = false;
	for(auto item = dynamic_cast<Logging_Message*>(Message_Relay::get_instance()->pop(logging_messages)); item != 0; item = dynamic_cast<Logging_Message*>(Message_Relay::get_instance()->pop(logging_messages)))
	{
		if(item->get_priority() == MESSAGE_PRIORITY::INFO_MESSAGE &&
		   item->get_location() == "Option Popup Creation" &&
		   item->get_message() == "Option Popup request recieved from subsystem ID" + std::to_string(static_cast<int>(SUBSYSTEM_ID_ENUM::TEST)))
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

	system_utilities::keyboard_utilities::connect = false;
	system_utilities::keyboard_utilities::Keyboard keyboard;
	system_utilities::sleep_thread(1000);
	Timer::Timeout keyboard_timer(5000);
	//keyboard start listening
	keyboard.get_interface()->connect_to_keyboard();
	keyboard.get_interface()->start_listening();
	keyboard_timer.start_clock();
	while(!keyboard.get_interface()->get_active() && !keyboard_timer.get_alarm());
	if(keyboard_timer.get_program_time() >= 5.0)
	{
		FAIL() << "Keyboard interface never activated. TEST BREAKING ERROR.";
	}
	keyboard.get_interface()->action_stack.change_action_layers(Predefined_Action_Layer::SIMPLE_BUFFERED_INPUT_LAYER);
	keyboard < KEY::NUM_1;
	keyboard < KEY::ENTER;

	while(keyboard.still_running());
}
