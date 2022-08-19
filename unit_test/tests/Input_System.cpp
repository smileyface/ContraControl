#include "../test_utilities/system_testings.h"
#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"

#include "../../dev/View/input_interface/keyboard_buffer_input.h"


namespace
{
	class Input_System_Test : public ::testing::Test
	{
	public:
		//Message_Consumer* consumer;
		virtual void SetUp()
		{
			system_utilities::setup();
		}
		virtual void TearDown()
		{

			system_utilities::cleanup();
		}
	};
}


TEST_F(Input_System_Test, Capture_Test)
{
	testing_utilities::input_utilities::wait_for_keypress(KEY::A);

}