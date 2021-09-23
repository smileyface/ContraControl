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

	EXPECT_EQ(received_state->valid, expected_state->valid) << "Device validity is not correct";
	EXPECT_EQ(received_state->initalized, expected_state->initalized) << "Device is not initalized properly";
	EXPECT_EQ(received_state->power, expected_state->power) << "Device power is not correct";
}

void testing_util::device_utilities::check_state(Device_Label device, Channel_Device* expected_state)
{
	Channel_Device* received_state = dynamic_cast<Channel_Device*>(model::get_device(device));


	EXPECT_EQ(received_state->valid, expected_state->valid) << "Device validity is not correct";
	EXPECT_EQ(received_state->initalized, expected_state->initalized) << "Device is not initalized properly";
	EXPECT_EQ(received_state->power, expected_state->power) << "Device power is not correct";
	EXPECT_EQ(received_state->transitioning, expected_state->transitioning) << "Device transition is not correct";
}

void testing_util::device_utilities::check_position(Device_Label label, Channel position)
{
	Gradient_Device* c_dev = dynamic_cast<Gradient_Device*>(model::get_device(label));
	EXPECT_EQ(c_dev->get_position(), position);
}



void testing_util::device_utilities::check_validity(Device_Label label, bool expect_valid)
{
	Device received_state = *model::get_device(label);

	EXPECT_EQ(received_state.valid, expect_valid) << "Device validity is not correct";
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
	case NETWORK_ERRORS::SOCKET_BUSY:
		FAIL() << "Socket is Busy";
		break;
	case NETWORK_ERRORS::NO_NETWORK_ERROR:
		FAIL() << "Network Subsystem has failed";
		break;
	case NETWORK_ERRORS::SERVER_CANNOT_START:
		FAIL() << "Server Cannot Start";
		break;
	case NETWORK_ERRORS::UNINITALIZED_INTERFACE:
		FAIL() << "Unintalized Interface";
	default:
		FAIL() << "Unknown Network Error ";
	}
}
