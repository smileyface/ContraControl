
#include "../utilities/device_utilities.h"
#include "../utilities/system_testings.h"
#include "../utilities/test_utilities.h"

#include "../utilities/pch.h"


namespace {
	class Gradient_Commands_Test : public ::testing::Test {
		virtual void SetUp() {
			system_util::setup();
		}
		virtual void TearDown() {
			system_util::cleanup();
		}

	};
}

TEST_F(Gradient_Commands_Test, Gradient_Initalize) {
	device_utilities::create_node("Test_Node_1");
	Device_Label dl = device_utilities::add_device("Test_Node_1", Device_Creator((int)DEVICE_IDENTIFIER::GRADIENT, "Test1"));
	device_utilities::initalize_device(dl);
	Device_State ds;
	ds.initalized = true;
	ds.valid = true;

	testing_util::device_utilities::check_state(dl, ds);

}

TEST_F(Gradient_Commands_Test, Gradient_On) {

	device_utilities::create_node("Test_Node_1");
	Device_Label dl = device_utilities::add_device("Test_Node_1", Device_Creator((int)DEVICE_IDENTIFIER::GRADIENT, "Test1"));
	device_utilities::initalize_device(dl);

	Device_State ds = device_utilities::command_device(dl, new On());
	testing_util::device_utilities::check_state(dl, ds);
}

TEST_F(Gradient_Commands_Test, Gradient_Off) {

	device_utilities::create_node("Test_Node_1");
	Device_Label dl = device_utilities::add_device("Test_Node_1", Device_Creator((int)DEVICE_IDENTIFIER::GRADIENT, "Test1"));
	device_utilities::initalize_device(dl);

	Device_State ds = device_utilities::command_device(dl, new On());
	testing_util::device_utilities::check_state(dl, ds);

	ds = device_utilities::command_device(dl, new Off());
	testing_util::device_utilities::check_state(dl, ds);

}

TEST_F(Gradient_Commands_Test, Gradient_Transition) {

	device_utilities::create_node("Test_Node_1");
	Device_Label dl = device_utilities::add_device("Test_Node_1", Device_Creator((int)DEVICE_IDENTIFIER::GRADIENT, "Test1"));
	device_utilities::initalize_device(dl);
	testing_util::device_utilities::check_position(dl, 0);

	//do transition
	auto time = model_timer.program_time;
	Transition* trans = new Transition(50, 20);
	Device_State ds = device_utilities::command_device(dl, trans);
	testing_util::device_utilities::check_state(dl, ds);
	ds = device_utilities::finish_command(trans);
	EXPECT_NEAR(model_timer.program_time - time, 20, .1);
	ds.transitioning = false;
	testing_util::device_utilities::check_state(dl, ds);
	testing_util::device_utilities::check_position(dl, 50);

}

TEST_F(Gradient_Commands_Test, Switch_Initalize) {
	device_utilities::create_node("Test_Node_1");
	Device_Label dl = device_utilities::add_device("Test_Node_1", Device_Creator((int)DEVICE_IDENTIFIER::SWITCH, "Test1"));
	device_utilities::initalize_device(dl);
	Device_State ds;
	ds.initalized = true;
	ds.valid = true;

	testing_util::device_utilities::check_state(dl, ds);
}