
#include "../test_utilities/device_utilities.h"
#include "../test_utilities/system_testings.h"
#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"


namespace {
	class Gradient_Commands_Test : public ::testing::Test {
	protected:
		Device_Label dl;
		virtual void SetUp() {
			system_util::setup();
			device_utilities::setup_node("Test_Node_Local", Node_Type::TEST);
			dl = device_utilities::add_device("Test_Node_Local", Device_Creator((int)DEVICE_IDENTIFIER::GRADIENT, "Test1"));
			device_utilities::initalize_device(dl);
		}
		virtual void TearDown() {
			system_util::cleanup();
		}

	};

	class Gradient_Commands_Test_No_Init : public ::testing::Test {
	protected:
		Device_Label dl;
		virtual void SetUp() {
			system_util::setup();
			device_utilities::setup_node("Test_Node_Local", Node_Type::TEST);
			dl = device_utilities::add_device("Test_Node_Local", Device_Creator((int)DEVICE_IDENTIFIER::GRADIENT, "Test1"));
		}
		virtual void TearDown() {
			system_util::cleanup();
		}

	};
}

TEST_F(Gradient_Commands_Test, Gradient_Initalize) {
	Gradient_Device* ds = new Gradient_Device();
	ds->initalized = true;
	ds->valid = true;

	testing_util::device_utilities::check_state(dl, ds);

}

TEST_F(Gradient_Commands_Test, Gradient_On) {

	Gradient_Device* ds = static_cast<Gradient_Device*>(device_utilities::command_device(dl, new On()));
	testing_util::device_utilities::check_state(dl, ds);
}

TEST_F(Gradient_Commands_Test, Gradient_Off) {
	Gradient_Device* ds = static_cast<Gradient_Device*>(device_utilities::command_device(dl, new On()));
	testing_util::device_utilities::check_state(dl, ds);

	ds = static_cast<Gradient_Device*>(device_utilities::command_device(dl, new Off()));
	testing_util::device_utilities::check_state(dl, ds);

}

TEST_F(Gradient_Commands_Test_No_Init, Gradient_Invalid) {
	device_utilities::command_device(dl, new Transition(0, 0));
	testing_util::device_utilities::check_validity(dl, false);

}

TEST_F(Gradient_Commands_Test, Gradient_Transition) {

	testing_util::device_utilities::check_position(dl, 0);

	//do transition
	auto time = model_timer.get_program_time();
	Transition* trans = new Transition(50, 20);
	Gradient_Device* ds = static_cast<Gradient_Device*>(device_utilities::command_device(dl, trans));
	testing_util::device_utilities::check_state(dl, ds);
	ds = static_cast<Gradient_Device*>(device_utilities::finish_command(dl, trans));
	EXPECT_NEAR(model_timer.get_program_time() - time, 20, .1);
	ds->transitioning = false;
	testing_util::device_utilities::check_state(dl, ds);
	testing_util::device_utilities::check_position(dl, 50);

}