#include "../test_utilities/device_utilities.h"
#include "../test_utilities/system_testings.h"
#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"

namespace {
	class NodeTest : public ::testing::Test {
		virtual void SetUp() {
			system_util::setup();
			device_utilities::setup_node("Test_Node_Local", Node_Type::TEST);
		}
		virtual void TearDown() {
			system_util::cleanup();
		}

	};
}
TEST_F(NodeTest, Node_Exclusion)
{
	device_utilities::create_node("Test_Node_2");
	Device_Label dl = device_utilities::add_device("Test_Node_Local", Device_Creator((int)DEVICE_IDENTIFIER::SWITCH, "Test1"));

	Device_Label dl_e("Test_Node_2", 0);
	
	ASSERT_THROW(device_utilities::command_device(dl_e, new On()), DeviceNotFoundException);

	Device_Label dl_e2("Test_Fail", 0);
	ASSERT_THROW(device_utilities::command_device(dl_e2, new Off()), NodeNotFoundException);
}
