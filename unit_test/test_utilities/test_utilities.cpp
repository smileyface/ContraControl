#include "test_utilities.h"
#include "system_testings.h"

#include "../../Network/network_main.h"

#include "pch.h"

#include <typeinfo>

void testing_utilities::log_top_test(Command* command, Device* device)
{
	Log_Entry topItem;
	EXPECT_NO_THROW(topItem = sys_log::pop()) << "Nothing happened. Log empty";
	EXPECT_EQ(topItem.device, device->get_full_name()) << "Wrong Device";
}

void testing_utilities::log_bottom_test(Command* command, Device* device)
{
	Log_Entry topItem;
	topItem = sys_log::drop();
}

void testing_utilities::get_partial_on(Command* command, Device* device, double timeout)
{
	while (timeout > 0)
	{
		system_utilities::step(1);
		timeout -= model_timer.get_elapsed_time();
	}
}

void testing_utilities::device_utilities::check_state(Device_Label device, Device* expected_state)
{
	Device* received_state = model::get_device(device);

	EXPECT_EQ(received_state->is_valid(), expected_state->is_valid()) << "Device validity is not correct";
	EXPECT_EQ(received_state->is_initalized(), expected_state->is_initalized()) << "Device is not initalized properly";
	EXPECT_EQ(received_state->get_power(), expected_state->get_power()) << "Device power is not correct";

}

void testing_utilities::device_utilities::check_validity(Device_Label label, bool expect_valid)
{
	Device received_state = *model::get_device(label);

	EXPECT_EQ(received_state.is_valid(), expect_valid) << "Device validity is not correct";
}

void testing_utilities::device_utilities::check_type(Device_Label label, DEVICE_IDENTIFIER type)
{
	EXPECT_EQ(model::get_device(label)->get_device_type(), type) << "Device type is incorrect";
}

void testing_utilities::device_utilities::check_channel(Device_Label label, int channel, Channel value)
{
	EXPECT_EQ(model::get_device(label)->get_channel(channel), value) << "Channel is incorrect";
}

void testing_utilities::device_utilities::check_channel(Device_Label label, Channel value)
{
	check_channel(label, 0, value);
}

void testing_utilities::device_utilities::check_name(Device_Label label, DEVICE_IDENTIFIER type, std::string name)
{
	EXPECT_EQ(model::get_device(label)->get_name(), name);
	std::string device_full_name = device_type_as_string(type) + "::" + name + "#" + std::to_string(model::get_device(label)->get_id());
	EXPECT_EQ(model::get_device(label)->get_full_name(), device_full_name);
}
void testing_utilities::node_utilities::check_for_device(Device_Label label)
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



void testing_utilities::network_utilities::check_initalized()
{
	network::network_interface->initalized();
	EXPECT_EQ(network::network_interface->get_status().status, NETWORK_STATUS::NETWORK_INITALIZED);
	if (network::network_interface->get_status().status == NETWORK_STATUS::NETWORK_ERROR)
	{
		exception_handle();
	}
}

void testing_utilities::network_utilities::exception_handle()
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
	case NETWORK_ERRORS::NETWORK_CODE_ERROR:
		FAIL() << "Code is incorrect. Debug.";
		break;
	case NETWORK_ERRORS::UNKNOWN_ERROR:
		FAIL() << "Unhandled Network Error";
		break;
	case NETWORK_ERRORS::NETWORK_OPTION_ERROR:
		FAIL() << "Invalid option error";
		break;
	default:
		FAIL() << "Unknown Network Error ";
	}
}

void testing_utilities::network_utilities::expect_exception(std::function<void()> function, NETWORK_ERRORS error)
{
	try
	{
		function();
	}
	catch (NetworkErrorException)
	{
		EXPECT_EQ(error, network::network_interface->get_status().error) << "The wrong error state was given";
		return;
	}
	FAIL() << "Network Error Exception did not throw";
}

void testing_utilities::network_utilities::network_message_utilities::check_header(int message_id, int size, std::vector<unsigned char> p_message)
{
	EXPECT_EQ(0x65, p_message[0]) << "Invalid Packet Header";
	EXPECT_EQ(message_id, p_message[1]) << "Incorrect Message Id";
	EXPECT_EQ(size, p_message[2]) << "Incorrect Packet Size";
}

void testing_utilities::network_utilities::network_message_utilities::compare_messages(PACKED_MESSAGE m1, PACKED_MESSAGE m2)
{
	MESSAGE_HEADER p_header, b_header;
	MESSAGE p_body, b_body;
	MESSAGE_FOOTER p_footer, b_footer;
	m1.get_message(p_header, p_body, p_footer);
	m2.get_message(b_header, b_body, b_footer);
	if (p_body.size() != b_body.size())
	{
		FAIL() << "Body sizes are not the same";
		return;
	}
	for (int i = 0; i < p_body.get_message().size(); i++)
	{
		if (typeid(p_body[i]) == typeid(Network_Address))
		{
			ipv4_addr p_addr = dynamic_cast<Network_Address*>(&p_body[i])->get_data();
			ipv4_addr b_addr = dynamic_cast<Network_Address*>(&b_body[i])->get_data();
			EXPECT_EQ(p_addr.S_un.S_addr, b_addr.S_un.S_addr) << "Addresses in position " << i << " are not the same";
		}
		else if (typeid(p_body[i]) == typeid(Network_String))
		{
			std::string p_str = dynamic_cast<Network_String*>(&p_body[1])->get_data().second;
			std::string b_str = dynamic_cast<Network_String*>(&b_body[1])->get_data().second;
			EXPECT_EQ(p_str, b_str) <<"String in position" << i << "are not the same";
			Byte p_length = dynamic_cast<Network_String*>(&p_body[1])->get_data().first;
			Byte b_length = dynamic_cast<Network_String*>(&b_body[1])->get_data().first;
			EXPECT_EQ(p_length, b_length) << "Length value of String in position" << i << "are not the same";;
		}
	}

}

void testing_utilities::subsystem_utilities::model_utilities::check_is_running(bool is_running)
{
	EXPECT_EQ(model::model_running, is_running);
}
