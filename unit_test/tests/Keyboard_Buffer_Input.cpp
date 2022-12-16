#include "../test_utilities/system_utilities.h"
#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"

#include "../View/input_interface/action_layer/action_stack.h"

namespace
{
	class Keyboard_Buffer_Input : public ::testing::Test
	{
	public:

		system_utilities::keyboard_utilities::Keyboard keyboard;
		Message_Consumer* consumer = 0;
		virtual void SetUp()
		{ 
			input_buffer.clear();
		}
		virtual void TearDown()
		{

			system_utilities::keyboard_utilities::tear_down();
		}
	};
}

TEST_F(Keyboard_Buffer_Input, Input_Buffer_Clear)
{

	keyboard < KEY::A;
	std::string read_buffer = input_buffer.get_buffer();
	EXPECT_EQ(read_buffer, "a");
	input_buffer.clear();
	keyboard < KEY::B;

	read_buffer = input_buffer.get_buffer();
	EXPECT_EQ(read_buffer, "b");
}

TEST_F(Keyboard_Buffer_Input, Buffer_Read_Alphabet)
{
	keyboard < KEY::A;
	keyboard < KEY::B;
	keyboard < KEY::C;
	keyboard.get_interface()->action_stack.get_active_layer()->handle_event(KEY::L_SHIFT, 1);
	keyboard < KEY::A;
	keyboard < KEY::B;
	keyboard < KEY::C;
	keyboard.get_interface()->action_stack.get_active_layer()->handle_event(KEY::L_SHIFT, 0);
	keyboard < KEY::A;
	keyboard < KEY::B;
	keyboard < KEY::C;

	std::string read_buffer = input_buffer.get_buffer();
	EXPECT_EQ(read_buffer, "abcABCabc");
}

TEST_F(Keyboard_Buffer_Input, Buffer_Read_Number_Line)
{
	keyboard < KEY::NUM_0;
	keyboard < KEY::NUM_1;
	keyboard < KEY::NUM_2;

	std::string read_buffer = input_buffer.get_buffer();
	EXPECT_EQ(read_buffer, "012");

	input_buffer.clear();

	keyboard.get_interface()->action_stack.get_active_layer()->handle_event(KEY::L_SHIFT, 1);
	keyboard < KEY::NUM_0;
	keyboard < KEY::NUM_1;
	keyboard < KEY::NUM_2;
	keyboard < KEY::NUM_3;
	keyboard < KEY::NUM_4;
	keyboard < KEY::NUM_5;
	keyboard < KEY::NUM_6;
	keyboard < KEY::NUM_7;
	keyboard < KEY::NUM_8;
	keyboard < KEY::NUM_9;
	keyboard.get_interface()->action_stack.get_active_layer()->handle_event(KEY::L_SHIFT, 0);

	read_buffer = input_buffer.get_buffer();
	EXPECT_EQ(read_buffer, ")!@#$%^&*(");

}

TEST_F(Keyboard_Buffer_Input, Buffer_Read_Number_Pad)
{
	keyboard < KEY::NUM_PAD::NUM_0;
	keyboard < KEY::NUM_PAD::NUM_1;
	keyboard < KEY::NUM_PAD::NUM_2;

	std::string read_buffer = input_buffer.get_buffer();
	EXPECT_EQ(read_buffer, "012");

}

TEST_F(Keyboard_Buffer_Input, Action_Layer_KPI_ASCII_Conversion_Tests)
{
	input_buffer.add(INVALID, KEY_STATE::PRESSED);

	std::string read_buffer = input_buffer.get_buffer();
	EXPECT_EQ(read_buffer, "");

	keyboard < KEY::ENTER;
	read_buffer = input_buffer.get_buffer();
#ifdef WIN32
	EXPECT_EQ(read_buffer, "\r\n");
#elif __linux__
	EXPECT_EQ(read_buffer, "\n");
#endif // WIN32

	input_buffer.clear();
	keyboard < KEY::TAB;
	read_buffer = input_buffer.get_buffer();

	EXPECT_EQ(read_buffer, "\t");
}
