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
		{ }
		virtual void TearDown()
		{

			system_utilities::keyboard_utilities::tear_down();
		}
	};
}

TEST_F(Keyboard_Buffer_Input, Buffer_Read)
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
