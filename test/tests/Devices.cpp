#include "../pch.h"

#include "../system_testings.h"

#include "../../dev/Model/model_main.h"


TEST(Devices, SwitchInitalize) {
	model::add_device("Device_1", new Switch_Device());

	system_util::setup();
	system_util::step(1);
	
	LogItem topItem;
	EXPECT_NO_THROW(topItem = sys_log::pop()) << "Nothing happened. Log empty";
	EXPECT_EQ(topItem.message, "Initalizing") << "Initalize failed";
	EXPECT_EQ(topItem.device, "Switch_Device::Device_1") << "Wrong Device";

	system_util::cleanup();
}

TEST(Devices, GradientInitalize) {
	model::add_device("Device_1", new Gradient_Device());

	system_util::setup();
	system_util::step(1);

	LogItem topItem;
	EXPECT_NO_THROW(topItem = sys_log::pop()) << "Nothing happened. Log empty";
	EXPECT_EQ(topItem.message, "Initalizing") << "Initalize failed";
	EXPECT_EQ(topItem.device, "Gradient_Device::Device_1") << "Wrong Device";

	system_util::cleanup();
}

