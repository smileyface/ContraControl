#include "../../test_utilities/device_utilities.h"
#include "../../test_utilities/system_utilities.h"
#include "../../test_utilities/test_utilities.h"

#include "../../test_utilities/pch.h"


namespace
{
	class Device_Invalid_Test : public ::testing::Test
	{
	protected:
		Device_Label dl;
		virtual void SetUp()
		{
			system_utilities::setup();
			system_utilities::start_system();
			device_utilities::start_test_environment();
			dl = device_utilities::add_device(Device_Creator((int) DEVICE_IDENTIFIER::INVALID, "Test1"));
		}
		virtual void TearDown()
		{
			system_utilities::stop_system();
			system_utilities::cleanup();
		}
	};
}

TEST_F(Device_Invalid_Test, Device_Invalid)
{
	testing_utilities::device_utilities::check_validity(dl, false);
}

TEST_F(Device_Invalid_Test, Device_Naming)
{
	device_utilities::command_device(dl, new Initalize_Device(dl, "Test1"));
	testing_utilities::device_utilities::check_name(dl, DEVICE_IDENTIFIER::INVALID, "Test1");
}