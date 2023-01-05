#include "../test_utilities/system_utilities.h"
#include "../test_utilities/test_utilities.h"
#include "../test_utilities/keyboard_interface_utilities.h"

#include "../test_utilities/pch.h"

#include "../../dev/View/input_interface/sys_interface/keyboard_interface.h"
#include "../../dev/View/input_interface/action_layer/predefined_layer.h"


namespace
{
	class Keyboard_System_Not_Connected_Test : public ::testing::Test
	{

	public:
		system_utilities::keyboard_utilities::Keyboard keyboard;
		virtual void SetUp() override
		{
			system_utilities::keyboard_utilities::connect = false;
			keyboard = system_utilities::keyboard_utilities::Keyboard();
			keyboard.get_interface()->connect_to_keyboard();
		}
		virtual void TearDown()
		{

		}
	private:
	};
}

TEST_F(Keyboard_System_Not_Connected_Test, Test_Loop)
{
	keyboard.get_interface()->start_listening();
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	keyboard.get_interface()->stop_listening();
	EXPECT_TRUE(((Test_Keyboard_Interface*) keyboard.get_interface())->read_a_character);
}

TEST_F(Keyboard_System_Not_Connected_Test, Test_Simple)
{
	std::string test1 = "";
	std::thread keyboard_test_thread = std::thread([&test1, this] () mutable
												   {
													   test1 = keyboard.get_interface()->get_simple();
												   });
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	Predefined_Action_Layer::Simple_Input_Layer::terminated = true;
	if(keyboard_test_thread.joinable())
	{
		keyboard_test_thread.join();
	}
	EXPECT_TRUE(Predefined_Action_Layer::Simple_Input_Layer::returned);
}

TEST_F(Keyboard_System_Not_Connected_Test, Test_Timeout)
{ 
	std::string test1 = "";
	std::thread keyboard_test_thread = std::thread([&test1, this] () mutable
												   {
													   test1 = keyboard.get_interface()->get_simple();
												   });
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	if(keyboard_test_thread.joinable())
	{
		keyboard_test_thread.join();
	}
	EXPECT_FALSE(Predefined_Action_Layer::Simple_Input_Layer::returned);
}
