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

TEST_F(Input_System_Test, Action_Layer_Test)
{
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
