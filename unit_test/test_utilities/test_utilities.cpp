#include "test_utilities.h"
#include "system_testings.h"

#include "pch.h"


#include <typeinfo>

void testing_util::log_top_test(Command* command, Device* device)
{
	LogItem topItem;
	EXPECT_NO_THROW(topItem = sys_log::pop()) << "Nothing happened. Log empty";
	EXPECT_EQ(topItem.device, device->get_full_name()) << "Wrong Device";
}

void testing_util::log_bottom_test(Command* command, Device* device)
{
	LogItem topItem;
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