#include "../../test_utilities/system_utilities.h"
#include "../../test_utilities/test_utilities.h"

#include "../../test_utilities/pch.h"

#include "../View/input_interface/keyboard_buffer_input.h"

namespace
{
	class Keyboard_Interface_Test : public ::testing::Test
	{
	public:

		system_utilities::keyboard_utilities::Keyboard keyboard;
		Message_Consumer* consumer = 0;
		virtual void SetUp()
		{
			system_utilities::setup();
			input_buffer.clear();
		}
		virtual void TearDown()
		{
			system_utilities::keyboard_utilities::tear_down();
			system_utilities::cleanup();
		}
	};
}

TEST_F(Keyboard_Interface_Test, Simple_Buffer)
{
	system_utilities::keyboard_utilities::Keyboard keyboard = system_utilities::keyboard_utilities::create_test_keyboard();
	keyboard.get_interface()->get_simple();
}