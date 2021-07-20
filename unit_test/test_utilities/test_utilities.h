#ifndef TESTING_UTILITIES_H
#define TESTING_UTILITIES_H

#include "../../dev/Model/model_main.h"
#include "../../dev/Controller/controller_main.h"

namespace testing_util
{
	void log_top_test(Command* command, Device* device);
	void log_bottom_test(Command* command, Device* device);
	void get_partial_on(Command* command, Device* device, double timeout);

	namespace device_utilities
	{
		void check_state(Device_Label label, Device* expected_state);
		void check_state(Device_Label device, Channel_Device* expected_state);
		void check_position(Device_Label label, Channel position);
		void check_validity(Device_Label label, bool expect_valid);
	}
	namespace network_utilities
	{

	}
}
#endif