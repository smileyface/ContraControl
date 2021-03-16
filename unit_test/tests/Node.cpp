#include "../utilities/device_utilities.h"
#include "../utilities/system_testings.h"
#include "../utilities/test_utilities.h"

#include "../utilities/pch.h"

namespace {
	class NodeTest : public ::testing::Test {
		virtual void SetUp() {
			system_util::setup();
		}
		virtual void TearDown() {
			system_util::cleanup();
		}

	};
}
TEST_F(NodeTest, Node_Exclusion)
{
	device_utilities::create_node("Test_Node_1");
	device_utilities::create_node("Test_Node_2");
	Device_Label dl = device_utilities::add_device("Test_Node_1", Device_Creator((int)DEVICE_IDENTIFIER::SWITCH, "Test1"));

	Device_Label dl_e("Test_Node_2", 0);
	
	ASSERT_THROW(device_utilities::command_device(dl_e, new On()), DeviceNotFoundException);

	dl_e.first = "Test_Fail";
	ASSERT_THROW(device_utilities::command_device(dl_e, new Off()), NodeNotFoundException);
}
