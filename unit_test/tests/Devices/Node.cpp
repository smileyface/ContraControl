#include "../../test_utilities/node_utilities.h"
#include "../../test_utilities/device_utilities.h"
#include "../../test_utilities/system_utilities.h"
#include "../../test_utilities/test_utilities.h"

#include "../../test_utilities/pch.h"

namespace {
	class Node_Test : public ::testing::Test {
		virtual void SetUp() {
			system_utilities::setup();
			system_utilities::start_system();
			node_utilities::start_test_environment();
		}
		virtual void TearDown() {
			system_utilities::stop_system();
			system_utilities::cleanup();
		}

	};
}

TEST_F(Node_Test, Node_Creation)
{
	node_utilities::create_node("Test_Node_2");
	Device_Label dl = node_utilities::add_device("Test_Node_2", Device_Creator((int) DEVICE_IDENTIFIER::SWITCH, "Test1"));
	
	EXPECT_NO_THROW(device_utilities::command_device(dl, Commander::get_instance()->make_command<On>(dl)));
}

TEST_F(Node_Test, Device_Exclusion)
{
	node_utilities::create_node("Test_Node_2");
	Device_Label dl = node_utilities::add_device(node_utilities::local_node_handle, Device_Creator((int) DEVICE_IDENTIFIER::SWITCH, "Test1"));

	Device_Label dl_e("Test_Node_2", 0);

	EXPECT_THROW(device_utilities::command_device(dl_e, Commander::get_instance()->make_command<On>(dl_e)), DeviceNotFoundException);
}

TEST_F(Node_Test, Node_Exclusion)
{
	Device_Label dl_e2("Test_Fail", 0);
	EXPECT_THROW(device_utilities::command_device(dl_e2, Commander::get_instance()->make_command<Off>(dl_e2)), NodeNotFoundException);
}

TEST_F(Node_Test, Add_Devices)
{
	Device_Label dl_n1_0 = node_utilities::add_device(node_utilities::local_node_handle, Device_Creator((int)DEVICE_IDENTIFIER::SWITCH, "Test1"));
	testing_utilities::node_utilities::check_for_device(dl_n1_0);
	Device_Label dl_n1_1 = node_utilities::add_device(node_utilities::local_node_handle, Device_Creator((int)DEVICE_IDENTIFIER::SWITCH, "Test2"));
	testing_utilities::node_utilities::check_for_device(dl_n1_0);
	testing_utilities::node_utilities::check_for_device(dl_n1_1);

	node_utilities::create_node("Test_Node_2");
	Device_Label dl_n2_0 = node_utilities::add_device("Test_Node_2", Device_Creator((int)DEVICE_IDENTIFIER::SWITCH, "Test2"));
	testing_utilities::node_utilities::check_for_device(dl_n2_0);
	testing_utilities::node_utilities::check_for_device(dl_n1_0);
}