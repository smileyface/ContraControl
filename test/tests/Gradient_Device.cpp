
#include "../utilities/pch.h"
#include "../utilities/system_testings.h"
#include "../utilities/test_utilities.h"

class Device_Commands: public ::testing::Test
{
	Device_Commands() {
		// initialization code here
	}

	void SetUp() {
		// code here will execute just before the test ensues 
	}

	void TearDown() {
		system_util::cleanup();

	}
};
TEST(Device_Commands, Gradient_Initalize) {
	model::add_device("Device_1", new Gradient_Device());
	system_util::setup();
	system_util::step(1);

	testing_util::log_top_test(new Initalize("non-sense"), model::get_device("Device_1"));
	EXPECT_EQ(dynamic_cast<Gradient_Device*>(model::get_device("Device_1"))->get_position(), 0) << "Device is not initalized properly";
}

TEST(Device_Commands, Gradient_On) {
	controller::add_command(Timed_Command(new On(), model::get_device("Device_1")->get_id(), 0));
	system_util::step(1);
	testing_util::log_top_test(new On(), model::get_device("Device_1"));
	EXPECT_EQ(dynamic_cast<Gradient_Device*>(model::known_devices["Device_1"])->get_position(), 1.0f) << "Device is not on";
}

TEST(Device_Commands, Gradient_Off) {
	controller::add_command(Timed_Command(new Off(), model::get_device("Device_1")->get_id(), 0));
	system_util::step(1);
	testing_util::log_top_test(new Off(), model::get_device("Device_1"));
	EXPECT_EQ(dynamic_cast<Gradient_Device*>(model::known_devices["Device_1"])->get_position(), 0.0f) << "Device is not off";
}

TEST(Device_Commands, Gradient_Transition) {
	Transition* trans = new Transition(50, 20);
	controller::add_command(Timed_Command(trans, model::get_device("Device_1")->get_id(), 0));
	system_util::step(1);
	testing_util::log_top_test(trans, model::get_device("Device_1"));
	EXPECT_EQ(dynamic_cast<Gradient_Device*>(model::known_devices["Device_1"])->get_position(), 0.5f) << "Device is not off";
}
