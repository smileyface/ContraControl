
#include "../utilities/device_utilities.h"
#include "../utilities/system_testings.h"

#include "../utilities/pch.h"

	TEST(Device_Commands, Gradient_Initalize) {
		std::string device = device_utilities::add_device(new Gradient_Device());
		device_utilities::initalize_device(device);
		Device_State ds;
		ds.initalized = true;
		ds.valid = true;

		device_utilities::check_state(device, ds);

		system_util::cleanup();
	}

	TEST(Device_Commands, Gradient_On) {
		std::string device = device_utilities::add_device(new Gradient_Device());
		device_utilities::initalize_device(device);
		Device_State ds = device_utilities::command_device(device, new On());
		device_utilities::check_state(device, ds);
		system_util::cleanup();
	}

	TEST(Device_Commands, Gradient_Off) {
		std::string device = device_utilities::add_device(new Gradient_Device());
		device_utilities::initalize_device(device);
		Device_State ds = device_utilities::command_device(device, new On());
		device_utilities::check_state(device, ds);

		ds = device_utilities::command_device(device, new Off());
		device_utilities::check_state(device, ds);

		system_util::cleanup();
	}

	TEST(Device_Commands, Gradient_Transition) {
		std::string device = device_utilities::add_device(new Gradient_Device());
		device_utilities::initalize_device(device);
		device_utilities::check_position(device, 0);

		//do transition
		auto time = model_timer.current_time;
		Transition* trans = new Transition(50, 200);
		Device_State ds = device_utilities::command_device(device, trans);
		device_utilities::check_state(device, ds);
		ds = device_utilities::finish_command(trans);
		ds.transitioning = false;
		EXPECT_NEAR(model_timer.current_time- time , 200, .1);
		device_utilities::check_state(device, ds);
		device_utilities::check_position(device, 50);

		system_util::cleanup();
	}
