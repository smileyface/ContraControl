#include "../../test_utilities/system_utilities.h"
#include "../../test_utilities/test_utilities.h"
#include "../../test_utilities/keyboard_interface_utilities.h"

#include "../../test_utilities/pch.h"

#include "../../dev/View/input_interface/sys_interface/keyboard_interface.h"
#include "../../dev/View/input_interface/action_layer/predefined_layer.h"


namespace
{
	class Keyboard_Interface_Test : public ::testing::Test
	{

	public:
		system_utilities::keyboard_utilities::Keyboard keyboard;
		virtual void SetUp() override
		{
			system_utilities::setup();
			system_utilities::keyboard_utilities::connect = false;
			keyboard = system_utilities::keyboard_utilities::Keyboard();
			keyboard.get_interface()->connect_to_keyboard();
		}
		virtual void TearDown()
		{
			system_utilities::cleanup();
		}
	private:
	};
}

TEST_F(Keyboard_Interface_Test, Test_Loop)
{
	keyboard.get_interface()->start_listening();
	system_utilities::sleep_thread(100);
	keyboard.get_interface()->stop_listening();
	EXPECT_TRUE(((Test_Keyboard_Interface*) keyboard.get_interface())->read_a_character);
}

TEST_F(Keyboard_Interface_Test, Test_Keyboard_Not_Connected)
{
	keyboard.get_interface()->disconnect_keyboard();
	keyboard.get_interface()->start_listening();
	EXPECT_FALSE(keyboard.get_interface()->get_active());
}

TEST_F(Keyboard_Interface_Test, Test_Keyboard_Plug_Pull)
{
	keyboard.get_interface()->start_listening();
	system_utilities::sleep_thread(100);
	keyboard.get_interface()->disconnect_keyboard();
	EXPECT_FALSE(keyboard.get_interface()->get_active());
}

TEST_F(Keyboard_Interface_Test, Test_Simple)
{
	std::string test1 = "";
	std::thread keyboard_test_thread = std::thread([&test1, this] () mutable
												   {
													   test1 = keyboard.get_interface()->get_simple();
												   });

	system_utilities::sleep_thread(100);
	EXPECT_TRUE(keyboard.keyboard_present());
	Predefined_Action_Layer::Simple_Input_Layer::terminated = true;
	if(keyboard_test_thread.joinable())
	{
		keyboard_test_thread.join();
	}
	EXPECT_TRUE(Predefined_Action_Layer::Simple_Input_Layer::returned);
}

TEST_F(Keyboard_Interface_Test, Test_Simple_Button_Presses)
{
	std::string test1 = "";
	std::thread keyboard_test_thread = std::thread([&test1, this] () mutable
												   {
													   test1 = keyboard.get_interface()->get_simple();
												   });
	system_utilities::sleep_thread(100);
	keyboard < KEY::A;
	keyboard < KEY::ENTER;
	if(keyboard_test_thread.joinable())
	{
		keyboard_test_thread.join();
	}
	EXPECT_TRUE(Predefined_Action_Layer::Simple_Input_Layer::returned);
	EXPECT_EQ(test1, "a");
}

TEST_F(Keyboard_Interface_Test, Test_Timeout)
{ 
	std::string test1 = "";
	std::thread keyboard_test_thread = std::thread([&test1, this] () mutable
												   {
													   test1 = keyboard.get_interface()->get_simple();
												   });
	system_utilities::sleep_thread(100);
	if(keyboard_test_thread.joinable())
	{
		keyboard_test_thread.join();
	}
	EXPECT_FALSE(Predefined_Action_Layer::Simple_Input_Layer::returned);
}
