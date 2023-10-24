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
	Node_Id temp_id = "Test_Node_2";
	node_utilities::create_node(temp_id);
	EXPECT_NO_THROW(model::get_node(temp_id));
	Device_Label dl = node_utilities::add_device(temp_id, Device_Creator((int) DEVICE_IDENTIFIER::SWITCH, "Test1"));
	
	Node* node = model::get_node(temp_id);
	EXPECT_EQ(node->get_id(), temp_id);
	EXPECT_EQ(node->get_devices().size(), 1);

	EXPECT_NO_THROW(device_utilities::command_device(dl, Commander::get_instance()->make_command<On>(dl)));
}

TEST_F(Node_Test, Node_Destruction)
{
	Node_Id temp_id = "Test_Node_2";
	node_utilities::create_node(temp_id);
	EXPECT_NO_THROW(model::get_node(temp_id));
	node_utilities::remove_node(temp_id);
	EXPECT_THROW(model::get_node(temp_id), NodeNotFoundException);
}

TEST_F(Node_Test, Node_Connection)
{
	Node_Id temp_id = "Test_Node_2";
	node_utilities::create_node(temp_id);
	node_utilities::connect_node(node_utilities::local_node_handle, temp_id);
	EXPECT_NO_THROW(model::get_node(node_utilities::local_node_handle)->get_connection(temp_id));
}

TEST_F(Node_Test, Node_Disconnect)
{
	Node_Id temp_id = "Test_Node_2";
	node_utilities::create_node(temp_id);
	node_utilities::connect_node(node_utilities::local_node_handle, temp_id);
	node_utilities::disconnect_node(node_utilities::local_node_handle, temp_id);
	EXPECT_THROW(model::get_node(node_utilities::local_node_handle)->get_connection(temp_id), NodeNotFoundException);
}

TEST_F(Node_Test, Device_Exclusion)
{
	node_utilities::create_node("Test_Node_2");
	Device_Label dl = node_utilities::add_device(node_utilities::local_node_handle, Device_Creator((int) DEVICE_IDENTIFIER::SWITCH, "Test1"));

	Device_Label dl_e("Test_Node_2", 0);

	testing_utilities::device_utilities::check_type(dl_e, DEVICE_IDENTIFIER::INVALID);
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