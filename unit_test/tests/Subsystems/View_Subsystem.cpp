#include "../../test_utilities/system_utilities.h"
#include "../../test_utilities/test_utilities.h"

#include "../../test_utilities/pch.h"

namespace
{
	class View_Subsystem_Test : public ::testing::Test
	{
	protected:
		virtual void SetUp()
		{
			system_utilities::setup();
		}
		virtual void TearDown()
		{
			system_utilities::cleanup();
		}
	};
}

TEST_F(View_Subsystem_Test, View_Test_Loop)
{
	system_utilities::view_utilities::start();
	testing_utilities::subsystem_utilities::view_utilities::check_is_running(true);
	system_utilities::sleep_thread(1000);
	system_utilities::view_utilities::stop();
	testing_utilities::subsystem_utilities::view_utilities::check_is_running(false);
}


TEST_F(View_Subsystem_Test, View_Test_Consumer)
{
	int consumers = Message_Relay::get_instance()->number_of_consumers();
	system_utilities::view_utilities::start();
	system_utilities::sleep_thread(1000);
	system_utilities::view_utilities::stop();
	ASSERT_EQ(Message_Relay::get_instance()->number_of_consumers(), consumers) << "View consumers not all removed.";
}

TEST_F(View_Subsystem_Test, View_Test_Memory_Leak)
{
	//TODO: This test <0.0.10

}

TEST_F(View_Subsystem_Test, View_Test_Keyboard_Input)
{

}

TEST_F(View_Subsystem_Test, View_Test_Display_Add_First)
{
	Message_Consumer* logging_messages = new Message_Consumer(new Logging_Message());
	view::add_display(DISPLAY_TYPES::CONSOLE);
	view::initalize();
	view::start_view();

	Option_Popup_Message* opm = dynamic_cast<Option_Popup_Message*>(Message_Relay::get_instance()->pop(logging_messages));

	view::stop_view();
	view::remove_all();

}
