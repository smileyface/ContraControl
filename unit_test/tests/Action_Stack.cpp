#include "../test_utilities/system_utilities.h"
#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"

namespace
{
	class Action_Stack_Test : public ::testing::Test
	{
	public:

		system_utilities::keyboard_utilities::Keyboard keyboard;
		Message_Consumer* consumer = 0;
		virtual void SetUp()
		{
			system_utilities::setup();
		}
		virtual void TearDown()
		{
			system_utilities::cleanup();
			system_utilities::keyboard_utilities::tear_down();
		}
	};
}

TEST_F(Action_Stack_Test, Event_Handle_Multilayer_Press_Button)
{
	bool the_good_one = false;

	int new_layer_index = keyboard.get_interface()->action_stack.add_action_layer();
	keyboard.get_interface()->action_stack.change_action_layers(new_layer_index);
	keyboard.get_interface()->action_stack.get_active_layer()->set_on_release(KEY::A,
																			  [&the_good_one] () mutable
																			  {
																				  the_good_one = true;
																			  });
	keyboard.get_interface()->action_stack.change_action_layers(0);
	keyboard < KEY::A;
	EXPECT_FALSE(the_good_one) << "The wrong layer was called";

	keyboard.get_interface()->action_stack.change_action_layers(new_layer_index);
	keyboard < KEY::A;
	EXPECT_TRUE(the_good_one) << "The on_press was not preserved";
}
