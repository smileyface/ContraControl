#include "../test_utilities/system_testings.h"
#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"



namespace
{
	class Input_System_Test : public ::testing::Test
	{
	public:

		system_utilities::keyboard_utilities::Keyboard keyboard;
		Message_Consumer* consumer;
		virtual void SetUp()
		{
			system_utilities::keyboard_utilities::setup();
		}
		virtual void TearDown()
		{

			system_utilities::keyboard_utilities::tear_down();
		}
	};
}

TEST_F(Input_System_Test, Action_Layer_Event_Handle_Test)
{
	bool is_pressed = false;
	bool is_released = false;
	bool is_held = false;
	keyboard.get_interface()->action_stack.get_active_layer()->set_on_press(KEY::A, 
																			[&is_pressed] () mutable
																			{
																				is_pressed = true;
																			});
	keyboard.get_interface()->action_stack.get_active_layer()->set_on_release(KEY::A,
																			  [&is_released] () mutable
																			  {
																				  is_released = true;
																			  });
	keyboard.get_interface()->action_stack.get_active_layer()->set_on_hold(KEY::A,
																			  [&is_held] () mutable
																			  {
																				  is_held = true;
																			  });
	
	int code = master_code_map[system_utilities::keyboard_utilities::get_char_from_kpi(KEY::A)].get_code();
	keyboard.get_interface()->action_stack.get_active_layer()->handle_event(code, 1);
	EXPECT_TRUE(is_pressed) << "Pressed was not handled";
	keyboard.get_interface()->action_stack.get_active_layer()->handle_event(code, 1);
	EXPECT_TRUE(is_held) << "Held was not handled";
	keyboard.get_interface()->action_stack.get_active_layer()->handle_event(code, 0);
	EXPECT_TRUE(is_released) << "Release was not handled";
}
TEST_F(Input_System_Test, Connection_Test)
{
	//Github Actions has input permission issues, so I'm not running that right now.
	if(!system_utilities::CI && !system_utilities::LINUX)
	{
		EXPECT_TRUE(keyboard.keyboard_present());
	}
}


TEST_F(Input_System_Test, Capture_Test)
{
	//Github Actions has input permission issues, so I'm not running that right now.
	if(!system_utilities::CI && !system_utilities::LINUX)
	{
		bool is_pressed = false;
		keyboard.set_key_operation(KEY::A, [&is_pressed] () mutable
								   {
									   is_pressed = true;
								   });
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		keyboard << system_utilities::keyboard_utilities::get_char_from_kpi(KEY::A);
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		EXPECT_TRUE(is_pressed);
	};
}
