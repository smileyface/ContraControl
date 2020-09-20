#include "test_utilities.h"

#include "pch.h"

void testing_util::log_top_test(Command* command, Device* device)
{
	LogItem topItem;
	EXPECT_NO_THROW(topItem = sys_log::pop()) << "Nothing happened. Log empty";
	EXPECT_EQ(topItem.message, command->get_log_entry()) << "Initalize failed";
	EXPECT_EQ(topItem.device, device->get_full_name()) << "Wrong Device";
}
