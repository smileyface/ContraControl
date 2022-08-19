#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"

#include "../../dev/View/input_interface/keyboard_buffer_input.h"


namespace
{
	class Input_System_Test : public ::testing::Test
	{
	public:
		Message_Consumer* consumer;
		bool found;
		virtual void SetUp()
		{
		}
		virtual void TearDown()
		{
		}
	};
}


TEST_F(Input_System_Test, Capture_Test)
{
	Keyboard_Buffer_Input buffer;
	buffer.keyboard->readEv();
}
