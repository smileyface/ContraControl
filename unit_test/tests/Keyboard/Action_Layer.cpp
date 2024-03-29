#include "../../test_utilities/system_utilities.h"
#include "../../test_utilities/test_utilities.h"

#include "../../test_utilities/pch.h"



namespace
{
	class Action_Layer_Test : public ::testing::Test
	{
	public:

		system_utilities::keyboard_utilities::Keyboard keyboard;
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

TEST_F(Action_Layer_Test, Action_Layer_Event_Handle_Test_On_Press)
{
	bool is_pressed = false;
	keyboard.get_interface()->action_stack.get_active_layer()->set_on_press(KEY::A, 
																			[&is_pressed] () mutable
																			{
																				is_pressed = true;
																			});
	keyboard.get_interface()->action_stack.get_active_layer()->handle_event(KEY::A, 1);
	EXPECT_TRUE(is_pressed) << "Pressed was not handled";
	EXPECT_EQ(keyboard.get_interface()->action_stack.get_active_layer()->get_pressed_state(KEY::A), KEY_STATE::PRESSED) << "Key is not in the pressed state";
	keyboard.get_interface()->action_stack.get_active_layer()->handle_event(KEY::A, 0);
}

TEST_F(Action_Layer_Test, Action_Layer_Event_Handle_Test_On_Hold)
{
	bool is_held = false;
	keyboard.get_interface()->action_stack.get_active_layer()->set_on_hold(KEY::A,
																		   [&is_held] () mutable
																		   {
																			   is_held = true;
																		   });
	keyboard.get_interface()->action_stack.get_active_layer()->handle_event(KEY::A, 1);
	EXPECT_FALSE(is_held) << "Hold was not handled";
	EXPECT_EQ(keyboard.get_interface()->action_stack.get_active_layer()->get_pressed_state(KEY::A), KEY_STATE::PRESSED) << "Key is not in the pressed state";
	keyboard.get_interface()->action_stack.get_active_layer()->handle_event(KEY::A, 1);
	EXPECT_TRUE(is_held) << "Hold was not handled";
	EXPECT_EQ(keyboard.get_interface()->action_stack.get_active_layer()->get_pressed_state(KEY::A), KEY_STATE::HELD) << "Key is not in the held state";
}

TEST_F(Action_Layer_Test, Action_Layer_Event_Handle_Test_On_Release)
{
	bool is_released = false;
	keyboard.get_interface()->action_stack.get_active_layer()->set_on_release(KEY::A,
																		   [&is_released] () mutable
																		   {
																				  is_released = true;
																		   });
	keyboard.get_interface()->action_stack.get_active_layer()->handle_event(KEY::A, 1);
	EXPECT_FALSE(is_released) << "Release was not handled";
	EXPECT_EQ(keyboard.get_interface()->action_stack.get_active_layer()->get_pressed_state(KEY::A), KEY_STATE::PRESSED) << "Key is not in the pressed state";
	keyboard.get_interface()->action_stack.get_active_layer()->handle_event(KEY::A, 0);
	EXPECT_TRUE(is_released) << "Release was not handled";
	EXPECT_EQ(keyboard.get_interface()->action_stack.get_active_layer()->get_pressed_state(KEY::A), KEY_STATE::RELEASED) << "Key is not in the released state";
}

TEST_F(Action_Layer_Test, Action_Layer_Event_Handle_Overridden_On_Press)
{
	bool the_good_one = false;
	bool the_bad_one = false;
	keyboard.get_interface()->action_stack.get_active_layer()->set_on_press(KEY::A,
																		   [&the_bad_one] () mutable
																		   {
																				  the_bad_one = true;
																		   });
	keyboard.get_interface()->action_stack.get_active_layer()->set_on_press(KEY::A,
																		   [&the_good_one] () mutable
																		   {
																				  the_good_one = true;
																		   });
	keyboard.get_interface()->action_stack.get_active_layer()->handle_event(KEY::A, 1);
	keyboard.get_interface()->action_stack.get_active_layer()->handle_event(KEY::A, 0);

	EXPECT_FALSE(the_bad_one) << "The function was not overriden";
	EXPECT_TRUE(the_good_one) << "The overridden function was not called";
}

TEST_F(Action_Layer_Test, Action_Layer_Event_Handle_Overridden_On_Hold)
{
	bool the_good_one = false;
	bool the_bad_one = false;
	keyboard.get_interface()->action_stack.get_active_layer()->set_on_hold(KEY::A,
																		   [&the_bad_one] () mutable
																		   {
																				  the_bad_one = true;
																		   });
	keyboard.get_interface()->action_stack.get_active_layer()->set_on_hold(KEY::A,
																		   [&the_good_one] () mutable
																		   {
																				  the_good_one = true;
																		   });
	keyboard.get_interface()->action_stack.get_active_layer()->handle_event(KEY::A, 1);
	keyboard.get_interface()->action_stack.get_active_layer()->handle_event(KEY::A, 1);
	keyboard.get_interface()->action_stack.get_active_layer()->handle_event(KEY::A, 0);

	EXPECT_FALSE(the_bad_one) << "The function was not overriden";
	EXPECT_TRUE(the_good_one) << "The overridden function was not called";
}

TEST_F(Action_Layer_Test, Action_Layer_Event_Handle_Overridden_On_Release)
{
	bool the_good_one = false;
	bool the_bad_one = false;
	keyboard.get_interface()->action_stack.get_active_layer()->set_on_release(KEY::A,
																		   [&the_bad_one] () mutable
																		   {
																				  the_bad_one = true;
																		   });
	keyboard.get_interface()->action_stack.get_active_layer()->set_on_release(KEY::A,
																		   [&the_good_one] () mutable
																		   {
																				  the_good_one = true;
																		   });
	keyboard.get_interface()->action_stack.get_active_layer()->handle_event(KEY::A, 1);
	keyboard.get_interface()->action_stack.get_active_layer()->handle_event(KEY::A, 0);

	EXPECT_FALSE(the_bad_one) << "The function was not overriden";
	EXPECT_TRUE(the_good_one) << "The overridden function was not called";
}

TEST_F(Action_Layer_Test, Action_Layer_Event_Handle_Multiple_Buttons)
{
	bool the_good_one = false;
	bool the_bad_one = false;
	keyboard.get_interface()->action_stack.get_active_layer()->set_on_release(KEY::A,
																		   [&the_bad_one] () mutable
																		   {
																				  the_bad_one = true;
																		   });
	keyboard.get_interface()->action_stack.get_active_layer()->set_on_release(KEY::B,
																		   [&the_good_one] () mutable
																		   {
																				  the_good_one = true;
																		   });
	keyboard.get_interface()->action_stack.get_active_layer()->handle_event(KEY::B, 1);
	keyboard.get_interface()->action_stack.get_active_layer()->handle_event(KEY::B, 0);

	EXPECT_FALSE(the_bad_one) << "The function was not overriden";
	EXPECT_TRUE(the_good_one) << "The overridden function was not called";
}

TEST_F(Action_Layer_Test, Action_Layer_Event_Handle_Press_Unhandled_Button)
{
	bool the_good_one = false;
	keyboard.get_interface()->action_stack.get_active_layer()->set_on_release(KEY::A,
																		   [&the_good_one] () mutable
																		   {
																				  the_good_one = true;
																		   });
	keyboard.get_interface()->action_stack.get_active_layer()->handle_event(KEY::C, 1);
	keyboard.get_interface()->action_stack.get_active_layer()->handle_event(KEY::C, 0);

	EXPECT_FALSE(the_good_one) << "The overridden function was not called";
}

TEST_F(Action_Layer_Test, Action_Layer_On_Hold_On_New_Layer)
{
	bool the_good_one = false;
	int new_layer_index = keyboard.get_interface()->action_stack.add_action_layer();
	keyboard.get_interface()->action_stack.change_action_layers(new_layer_index);
	keyboard.get_interface()->action_stack.get_active_layer()->set_on_hold(KEY::A,
																		   [&the_good_one] () mutable
																		   {
																				  the_good_one = true;
																		   });

	keyboard.get_interface()->action_stack.get_active_layer()->handle_event(KEY::A, 1);
	keyboard.get_interface()->action_stack.get_active_layer()->handle_event(KEY::A, 1);
	keyboard.get_interface()->action_stack.get_active_layer()->handle_event(KEY::A, 0);
	EXPECT_TRUE(the_good_one) << "The overridden function was not called";
}

TEST_F(Action_Layer_Test, Action_Layer_Dont_Press_The_Button)
{
	bool the_good_one = false;
	keyboard.get_interface()->action_stack.get_active_layer()->set_on_press(KEY::A,
																			[&the_good_one] () mutable
																			{
																				the_good_one = true;
																			});
	keyboard.get_interface()->action_stack.get_active_layer()->set_on_hold(KEY::A,
																		   [&the_good_one] () mutable
																		   {
																			   the_good_one = true;
																		   });
	keyboard.get_interface()->action_stack.get_active_layer()->set_on_release(KEY::A,
																			  [&the_good_one] () mutable
																			  {
																				  the_good_one = true;
																			  });
	keyboard.get_interface()->action_stack.get_active_layer()->handle_event(KEY::A, 0);

	EXPECT_FALSE(the_good_one);
}
