#include "../../test_utilities/device_utilities.h"
#include "../../test_utilities/system_utilities.h"
#include "../../test_utilities/test_utilities.h"

#include "../../test_utilities/pch.h"


namespace {
	class Commands_Test : public ::testing::Test {
	protected:
		Device_Label dl;
		virtual void SetUp() {
			system_utilities::setup();
			system_utilities::start_system();
			device_utilities::start_test_environment();
			dl = device_utilities::add_device(Device_Creator((int)DEVICE_IDENTIFIER::SWITCH, "Test1"));
		}
		virtual void TearDown() {
			system_utilities::stop_system();
			system_utilities::cleanup();
		}
		void switch_to_device(DEVICE_IDENTIFIER device_type) {
			device_utilities::remove_device(dl);
			dl = device_utilities::add_device(Device_Creator((int)device_type, "Test1"));
		}
	};
}

TEST_F(Commands_Test, Device_Initalize) 
{
	Device* ds = create_device_instance(Device_Creator((int)DEVICE_IDENTIFIER::SWITCH, "Results"));
	testing_utilities::device_utilities::check_state(dl, ds);
	ds = static_cast<Device*>(device_utilities::command_device(dl, Commander::get_instance()->make_command<Initalize_Device>(dl, "Test1")));
	testing_utilities::device_utilities::check_state(dl, ds);
}
TEST_F(Commands_Test, Device_On)
{
	Device* ds = static_cast<Device*>(device_utilities::command_device(dl, Commander::get_instance()->make_command<On>(dl)));
	testing_utilities::device_utilities::check_state(dl, ds);
	ds = static_cast<Device*>(device_utilities::command_device(dl, Commander::get_instance()->make_command<Initalize_Device>(dl, "Test1")));
	ds = static_cast<Device*>(device_utilities::command_device(dl, Commander::get_instance()->make_command<On>(dl)));
	testing_utilities::device_utilities::check_state(dl, ds);
}

TEST_F(Commands_Test, Device_Off) 
{
	Device * ds = static_cast<Device*>(device_utilities::command_device(dl, Commander::get_instance()->make_command<Off>(dl)));
	testing_utilities::device_utilities::check_state(dl, ds);
	ds = static_cast<Device*>(device_utilities::command_device(dl, Commander::get_instance()->make_command<Initalize_Device>(dl, "Test1")));
	ds = static_cast<Device*>(device_utilities::command_device(dl, Commander::get_instance()->make_command<On>(dl)));
	testing_utilities::device_utilities::check_state(dl, ds);

	ds = static_cast<Device*>(device_utilities::command_device(dl, Commander::get_instance()->make_command<Off>(dl)));
	testing_utilities::device_utilities::check_state(dl, ds);
}

TEST_F(Commands_Test, Device_Assign_Channel) 
{
	dl = device_utilities::add_device(Device_Creator((int)DEVICE_IDENTIFIER::GRADIENT, "Test1"));
	Device* ds = static_cast<Device*>(device_utilities::command_device(dl, Commander::get_instance()->make_command <Assign>(dl, 50)));
	testing_utilities::device_utilities::check_channel(dl, 50);

	dl = device_utilities::add_device(Device_Creator((int)DEVICE_IDENTIFIER::RGB, "RGB_Tester"));
	ds = static_cast<Device*>(device_utilities::command_device(dl, Commander::get_instance()->make_command <Assign>(dl, 2, 50)));
	testing_utilities::device_utilities::check_channel(dl, 2, 50);
	testing_utilities::device_utilities::check_channel(dl, 1, 0);
	testing_utilities::device_utilities::check_channel(dl, 0, 0);
}

TEST_F(Commands_Test, Device_Invalid_Command) 
{
	EXPECT_THROW(device_utilities::command_device(dl, new Command()), InvalidCommandException);
}

/*This test and concept needs a redesign*/
//This has become undefined behavior

TEST_F(Commands_Test, Device_Duplicate_Command)
{

}