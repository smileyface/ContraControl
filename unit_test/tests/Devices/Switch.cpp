#include "../../test_utilities/device_utilities.h"
#include "../../test_utilities/system_utilities.h"
#include "../../test_utilities/test_utilities.h"

#include "../../test_utilities/pch.h"


namespace
{
	class Device_Switch_Test : public ::testing::Test
	{
	protected:
		Device_Label dl;
		virtual void SetUp()
		{
			system_utilities::setup();
			system_utilities::start_system();
			device_utilities::start_test_environment();
			dl = device_utilities::add_device(Device_Creator((int) DEVICE_IDENTIFIER::SWITCH, "Test1"));
		}
		virtual void TearDown()
		{
			system_utilities::stop_system();
			system_utilities::cleanup();
		}
	};
}

TEST_F(Device_Switch_Test, Device_Created)
{
	testing_utilities::device_utilities::check_type(dl, DEVICE_IDENTIFIER::SWITCH);
}
TEST_F(Device_Switch_Test, Device_Invalid)
{
	testing_utilities::device_utilities::check_validity(dl, false);
	device_utilities::command_device(dl, Commander::get_instance()->make_command<Initalize_Device>(dl, "Test1"));
	testing_utilities::device_utilities::check_validity(dl, true);
}
TEST_F(Device_Switch_Test, Device_Removed)
{
	testing_utilities::device_utilities::check_type(dl, DEVICE_IDENTIFIER::SWITCH);
	device_utilities::remove_device(dl);
	testing_utilities::device_utilities::check_type(dl, DEVICE_IDENTIFIER::INVALID);
}
TEST_F(Device_Switch_Test, Device_Naming)
{
	device_utilities::command_device(dl, Commander::get_instance()->make_command<Initalize_Device>(dl, "Test1"));
	testing_utilities::device_utilities::check_name(dl, DEVICE_IDENTIFIER::SWITCH, "Test1");
}
