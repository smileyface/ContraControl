#ifndef TESTING_UTILITIES_H
#define TESTING_UTILITIES_H

#include <utility>

#include "../../dev/Model/model_main.h"
#include "../../dev/Controller/controller_main.h"


#include "../../dev/Utilities/Utilities/exceptions.h"

namespace testing_util
{
	void log_top_test(Command* command, Device* device);
	void log_bottom_test(Command* command, Device* device);
	void get_partial_on(Command* command, Device* device, double timeout);

	extern std::pair<int, int> test_point_succeeded_ratio;

	namespace device_utilities
	{
		void check_state(Device_Label label, Device* expected_state);
		void check_position(Device_Label label, Channel position);
		void check_validity(Device_Label label, bool expect_valid);
		void check_type(Device_Label label, DEVICE_IDENTIFIER id);
		void check_power_for_real(Device_Label label);
		void check_channel(Device_Label label, int channel, Channel value);
		void check_channel(Device_Label label, Channel value);
	}
	namespace node_utilities
	{
		void check_for_device(Device_Label label);
	}
	namespace network_utilities
	{
		void check_initalized();
		void exception_handle();
	}
}

namespace network_test_util
{
	
}
#endif