#include "../test_utilities/test_utilities.h"
#include "../test_utilities/system_utilities.h"

#include "../test_utilities/pch.h"

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
		Message_Consumer* logging_messages;
		Message_Consumer* option_consumer;
		bool found = false;
		Command_View_Message_Test()
		{
			logging_messages = new Message_Consumer(new Logging_Message());
			option_consumer = new Message_Consumer(new Option_Popup_Message());
		}
		~Command_View_Message_Test()
		{
			delete logging_messages;
			delete option_consumer;
		}
		virtual void SetUp()
		{

			system_utilities::setup();
			Message_Relay::get_instance()->register_consumer(logging_messages);
			Message_Relay::get_instance()->register_consumer(option_consumer);
		}
		virtual void TearDown()
		{
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
	Option_Popup_Message* opm = dynamic_cast<Option_Popup_Message*>(Message_Relay::get_instance()->pop(option_consumer));
	EXPECT_FALSE(found);
	EXPECT_EQ(opm->get_sender(), SUBSYSTEM_ID_ENUM::TEST);
	Option_List list=opm->get_options();
	EXPECT_EQ(list[0], "Hello");
	EXPECT_EQ(list[1], "It's");
	EXPECT_EQ(list[2], "Me");

	view::add_display(DISPLAY_TYPES::CONSOLE);
	view::initalize();
	view::start_view();
	Message_Relay::get_instance()->push(opm);
	system_utilities::sleep_thread(1000);
	view::stop_view();
	view::remove_all();
	while(view::view_running);
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

TEST_F(Command_View_Message_Test, Select_Option)
{
	Message_Relay::get_instance()->push(new Option_Popup_Message(SUBSYSTEM_ID_ENUM::TEST, "Tester", { "Hello", "It's", "Me" }));

	view::add_display(DISPLAY_TYPES::CONSOLE);
	view::initalize();
	view::start_view();

	system_utilities::keyboard_utilities::connect = false;
	system_utilities::keyboard_utilities::Keyboard keyboard;
	system_utilities::sleep_thread(1000);
	keyboard.get_interface()->action_stack.change_action_layers(Predefined_Action_Layer::SIMPLE_BUFFERED_INPUT_LAYER);
	keyboard < KEY::NUM_1;
	keyboard < KEY::ENTER;
	Timer::Timeout keyboard_timer(5000);
	while(keyboard.get_interface()->get_active() && !keyboard_timer.get_alarm());
	if(keyboard_timer.get_program_time() > 5.0)
	{
		FAIL() << "Keyboard interface never activated. TEST BREAKING ERROR.";
	}
	std::vector<Logging_Message*> logs;
	for(auto item = dynamic_cast<Logging_Message*>(Message_Relay::get_instance()->pop(logging_messages)); item != 0; item = dynamic_cast<Logging_Message*>(Message_Relay::get_instance()->pop(logging_messages)))
	{
		logs.push_back(item);
	}
	view::stop_view();
	view::remove_all();
}
