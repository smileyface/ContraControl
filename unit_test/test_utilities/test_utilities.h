#ifndef TESTING_UTILITIES_H
#define TESTING_UTILITIES_H

#define DEBUG

#include <utility>
#include <functional>

#include "../../dev/Model/model_main.h"
#include "../../dev/Controller/controller_main.h"

#include "../../dev/Utilities/Utilities/exceptions.h"
#include "../../dev/Network/system_interfaces/types/network_status_state.h"
#include "../../dev/Network/messages/messaging.h"

namespace testing_utilities
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
		void check_name(Device_Label label, DEVICE_IDENTIFIER type, std::string name);
	}
	namespace node_utilities
	{
		void check_for_device(Device_Label label);
	}
	namespace network_utilities
	{
		void check_initalized();
		void exception_handle();
		void expect_exception(std::function<void()> function, NETWORK_ERRORS error);
		namespace network_message_utilities
		{
			void check_header(int message_id, int size, std::vector<unsigned char> p_message);
			void compare_header(Packed_Message p, Unpacked_Message u);
			void compare_footer(Packed_Message p, Unpacked_Message u);
			void compare_messages(Unpacked_Message b, Network_Message m);
			void compare_messages(Packed_Message p, Network_Message m);
		}
	}
	namespace subsystem_utilities
	{
		namespace model_utilities
		{
			void check_is_running(bool is_running);
		}
	}
	namespace error_utilities
	{
		void check_override_failure(std::function<void()> function);
	}
}
#endif