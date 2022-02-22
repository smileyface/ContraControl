#include "test_utilities.h"
#include "system_testings.h"

#include "Network/system_interfaces/network_interface.h"

#include "pch.h"

#include <typeinfo>

void testing_util::log_top_test(Command* command, Device* device)
{
	Log_Entry topItem;
	EXPECT_NO_THROW(topItem = sys_log::pop()) << "Nothing happened. Log empty";
	EXPECT_EQ(topItem.device, device->get_full_name()) << "Wrong Device";
}

void testing_util::log_bottom_test(Command* command, Device* device)
{
	Log_Entry topItem;
	topItem = sys_log::drop();
}

void testing_util::get_partial_on(Command* command, Device* device, double timeout)
{
	while (timeout > 0)
	{
		system_util::step(1);
		timeout -= model_timer.get_elapsed_time();
	}
}

void testing_util::device_utilities::check_state(Device_Label device, Device* expected_state)
{
	Device* received_state = model::get_device(device);

	EXPECT_EQ(received_state->is_valid(), expected_state->is_valid()) << "Device validity is not correct";
	EXPECT_EQ(received_state->is_initalized(), expected_state->is_initalized()) << "Device is not initalized properly";
	EXPECT_EQ(received_state->get_power(), expected_state->get_power()) << "Device power is not correct";

}

void testing_util::device_utilities::check_validity(Device_Label label, bool expect_valid)
{
	Device received_state = *model::get_device(label);

	EXPECT_EQ(received_state.is_valid(), expect_valid) << "Device validity is not correct";
}

void testing_util::device_utilities::check_type(Device_Label label, DEVICE_IDENTIFIER type)
{
	EXPECT_EQ(model::get_device(label)->get_device_type(), type) << "Device type is incorrect";
}

void testing_util::node_utilities::check_for_device(Device_Label label)
{
	bool found = false;
	for (int i = 0; i < model::get_node(label.get_node_id())->get_devices().size(); i++)
	{
		if (model::get_node(label.get_node_id())->get_devices()[i] == label.get_device_id())
		{
			found = true;
		}
	}
	EXPECT_EQ(found, true);
}

void testing_util::network_utilities::check_initalized()
{
	network::network_interface->initalized();
	EXPECT_EQ(network::network_interface->get_status().status, NETWORK_STATUS::NETWORK_INITALIZED);
	if (network::network_interface->get_status().status == NETWORK_STATUS::NETWORK_ERROR)
	{

	}
}

void testing_util::network_utilities::exception_handle()
{
	switch (network::network_interface->get_status().error)
	{
	case NETWORK_ERRORS::NO_NETWORK_ERROR:
		FAIL() << "Network Subsystem has failed";
		break;
	case NETWORK_ERRORS::UNINITALIZED_INTERFACE:
		FAIL() << "Unintalized Interface";
		break;
	case NETWORK_ERRORS::ADAPTER_ERROR:
		FAIL() << "Adapter Error";
		break;
	case NETWORK_ERRORS::SOCKET_INVALID:
		FAIL() << "Invalid Socket";
		break;
	case NETWORK_ERRORS::INVALID_HOSTNAME:
		FAIL() << "Invalid Hostname";
		break;
	case NETWORK_ERRORS::ERROR_ON_SOCKET_BIND:
		FAIL() << "Socket Bind Failed";
		break;
	case NETWORK_ERRORS::ERROR_ON_SOCKET_LISTEN:
		FAIL() << "Error listening on socket";
		break;
	case NETWORK_ERRORS::SYSTEM_INTERFACE_ERROR:
		FAIL() << "Error grabbing the interface";
		break;
	case NETWORK_ERRORS::SOCKET_BUSY:
		FAIL() << "Socket is Busy";
		break;
	case NETWORK_ERRORS::SERVER_CANNOT_START:
		FAIL() << "Server Cannot Start";
		break;

	case NETWORK_ERRORS::UNKNOWN_ERROR:
		FAIL() << "Unhandled Network Error";
		break;
	default:
		FAIL() << "Unknown Network Error ";
	}
}
