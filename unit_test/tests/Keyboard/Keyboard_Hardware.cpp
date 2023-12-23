#include "../../test_utilities/system_utilities.h"
#include "../../test_utilities/test_utilities.h"

#include "../../test_utilities/pch.h"

#include "../../dev/View/input_interface/action_layer/predefined_layer.h"

namespace
{
	class Keyboard_Hardware_Test : public ::testing::Test
	{
	public:

		system_utilities::keyboard_utilities::Keyboard keyboard;
		Message_Consumer* consumer = 0;
		virtual void SetUp() override
		{
			system_utilities::setup();
			keyboard.get_interface()->connect_to_keyboard();
			keyboard.get_interface()->start_listening();

			if(system_utilities::CI && system_utilities::LINUX)
			{
				LOG_INFO("Skipping hardware interface test on Linux CI", "Keyboard test setup");
				GTEST_SKIP() << "Github Actions has input permission issues on Linux, so I'm not running those tests right now.\nPlease make sure you've run these tests locally before merging the PR.";
			}
		}
		virtual void TearDown()
		{
			keyboard.get_interface()->stop_listening();
			system_utilities::keyboard_utilities::tear_down();
			system_utilities::cleanup();
		}
	};
}

TEST_F(Keyboard_Hardware_Test, Connection_Test)
{
	EXPECT_TRUE(keyboard.keyboard_present());
}


TEST_F(Keyboard_Hardware_Test, Capture_Test)
{
	bool is_pressed = false;
	keyboard.set_key_operation(KEY::A, [&is_pressed] () mutable
							   {
								   is_pressed = true;
							   });
	system_utilities::sleep_thread(100);
	keyboard << system_utilities::keyboard_utilities::get_char_from_kpi(KEY::A);
	system_utilities::sleep_thread(100);
	EXPECT_TRUE(is_pressed);
}

TEST_F(Keyboard_Hardware_Test, Keyboard_Input_Simple)
{
	std::string test1 = "";
	std::thread keyboard_test_thread = std::thread([&test1, this] () mutable
												   {
													   test1 = keyboard.get_interface()->get_simple();
												   });
	system_utilities::sleep_thread(100);
	keyboard << system_utilities::keyboard_utilities::get_char_from_kpi(KEY::T);
	keyboard << system_utilities::keyboard_utilities::get_char_from_kpi(KEY::E);
	keyboard << system_utilities::keyboard_utilities::get_char_from_kpi(KEY::S);
	keyboard << system_utilities::keyboard_utilities::get_char_from_kpi(KEY::T);
	keyboard << system_utilities::keyboard_utilities::get_char_from_kpi(KEY::ENTER);
	if(keyboard_test_thread.joinable())
	{
		keyboard_test_thread.join();
	}

	EXPECT_EQ(test1, "test");
}

TEST_F(Keyboard_Hardware_Test, Keyboard_Input_Double_Identical_Character)
{
	std::string test1 = "";
	std::thread keyboard_test_thread = std::thread([&test1, this] () mutable
												   {
													   test1 = keyboard.get_interface()->get_simple();
												   });
	system_utilities::sleep_thread(100);
	keyboard << system_utilities::keyboard_utilities::get_char_from_kpi(KEY::A);
	keyboard << system_utilities::keyboard_utilities::get_char_from_kpi(KEY::A);
	keyboard << system_utilities::keyboard_utilities::get_char_from_kpi(KEY::ENTER);

	if(keyboard_test_thread.joinable())
	{
		keyboard_test_thread.join();
	}

	EXPECT_EQ(test1, "aa");
}

TEST_F(Keyboard_Hardware_Test, Keyboard_Input_Twice)
{
	std::string test1 = "";
	std::thread keyboard_test_thread = std::thread([&test1, this] () mutable
												   {
													   test1 = keyboard.get_interface()->get_simple();
												   });
	system_utilities::sleep_thread(100);
	keyboard << system_utilities::keyboard_utilities::get_char_from_kpi(KEY::A);
	keyboard << system_utilities::keyboard_utilities::get_char_from_kpi(KEY::A);
	keyboard << system_utilities::keyboard_utilities::get_char_from_kpi(KEY::ENTER);

	if(keyboard_test_thread.joinable())
	{
		keyboard_test_thread.join();
	}

	EXPECT_EQ(test1, "aa");

	test1 = "";
	std::thread keyboard_test_thread2 = std::thread([&test1, this] () mutable
													{
														test1 = keyboard.get_interface()->get_simple();
													});
	system_utilities::sleep_thread(100);

	keyboard << system_utilities::keyboard_utilities::get_char_from_kpi(KEY::B);
	keyboard << system_utilities::keyboard_utilities::get_char_from_kpi(KEY::B);
	keyboard << system_utilities::keyboard_utilities::get_char_from_kpi(KEY::ENTER);

	if(keyboard_test_thread2.joinable())
	{
		keyboard_test_thread2.join();
	}
	EXPECT_EQ(test1, "bb");
}