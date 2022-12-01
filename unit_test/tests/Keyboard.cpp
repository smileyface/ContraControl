#include "../test_utilities/system_utilities.h"
#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"

namespace
{
	class Keyboard_Test : public ::testing::Test
	{
	public:

		system_utilities::keyboard_utilities::Keyboard keyboard;
		Message_Consumer* consumer = 0;
		virtual void SetUp()
		{
			keyboard.get_interface()->connect_to_keyboard();
			keyboard.get_interface()->start_listening();
		}
		virtual void TearDown()
		{
			keyboard.get_interface()->stop_listening();
			system_utilities::keyboard_utilities::tear_down();
		}
	};
}

TEST_F(Keyboard_Test, Connection_Test)
{
	//Github Actions has input permission issues, so I'm not running that right now.
	if(!system_utilities::CI && !system_utilities::LINUX)
	{
		EXPECT_TRUE(keyboard.keyboard_present());
	}
}


TEST_F(Keyboard_Test, Capture_Test)
{
	//Github Actions has input permission issues, so I'm not running that right now.
	if(!system_utilities::CI && !system_utilities::LINUX)
	{
		bool is_pressed = false;
		keyboard.set_key_operation(KEY::A, [&is_pressed] () mutable
								   {
									   is_pressed = true;
								   });
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		keyboard << system_utilities::keyboard_utilities::get_char_from_kpi(KEY::A);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		EXPECT_TRUE(is_pressed);
	};
}