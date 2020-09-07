
#include "../pch.h"
#include "../system_testings.h"
#include "../../dev/Interfaces/controller_interface.h"
#include "../../dev/Model/model_main.h"

TEST(Commands, Initalize) {
	model::known_devices.emplace("Device_1", new Device());
	system_util::setup();


	Device_Id device_id = controller_interfaces::model_interface::get_device("Device_1").get_id();
	controller_interfaces::model_interface::send_command(Timed_Command(new Initalize("Device_1"),device_id , 0));

	system_util::step(1);

	LogItem topItem;
	EXPECT_NO_THROW(topItem = sys_log::pop()) << "Nothing happened. Log empty";
	EXPECT_EQ(topItem.message, "Initalizing") << "Initalize failed";
	EXPECT_EQ(topItem.device, "Device::Device_1") << "Wrong Device";

	system_util::cleanup();
}

TEST(Commands, Level) {
	FAIL() << "Not Implemented";

}

TEST(Commands, Off) {
	FAIL() << "Not Implemented";

}

TEST(Commands, On) {
	FAIL() << "Not Implemented";

}
