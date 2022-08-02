#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"

#include "../../dev/Interfaces/Messaging/message_relay.h"
#include "../../dev/View/view_main.h"

namespace
{
	class Command_View_Message_Test : public ::testing::Test
	{
	public:
		Message_Consumer* logging_messages = new Message_Consumer(new Logging_Message());
		Message_Consumer* option_consumer = new Message_Consumer(new Option_Popup_Message());
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
	Message_Relay::get_instance()->push(new Option_Popup_Message(SUBSYSTEM_ID_ENUM::TEST, { "Hello", "It's", "Me" }));
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
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
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



	view::stop_view();
}