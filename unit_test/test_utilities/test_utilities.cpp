#include "test_utilities.h"
#include "system_utilities.h"

#include "../../Network/network_main.h"

#include "pch.h"

#include <typeinfo>

template <typename T> char const* str_type(T const& obj)
{
	return typeid(obj).name();
}
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
	while(timeout > 0)
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
	for(int i = 0; i < model::get_node(label.get_node_id())->get_devices().size(); i++)
	{
		if(model::get_node(label.get_node_id())->get_devices()[i] == label.get_device_id())
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
	if(network::network_interface->get_status().status == NETWORK_STATUS::NETWORK_ERROR)
	{
		exception_handle();
	}
}

std::string get_string_of_error(NETWORK_ERRORS errors)
{
	switch(errors)
	{
	case NETWORK_ERRORS::NO_NETWORK_ERROR:
		return "Network Subsystem has failed";
	case NETWORK_ERRORS::UNINITALIZED_INTERFACE:
		return "Unintalized Interface";
	case NETWORK_ERRORS::ADAPTER_ERROR:
		return "Adapter Error";
	case NETWORK_ERRORS::SOCKET_INVALID:
		return "Invalid Socket";
	case NETWORK_ERRORS::INVALID_HOSTNAME:
		return "Invalid Hostname";
	case NETWORK_ERRORS::ERROR_ON_SOCKET_BIND:
		return "Socket Bind Failed";
	case NETWORK_ERRORS::ERROR_ON_SOCKET_LISTEN:
		return "Error listening on socket";
	case NETWORK_ERRORS::SYSTEM_INTERFACE_ERROR:
		return "Error grabbing the interface";
	case NETWORK_ERRORS::SOCKET_BUSY:
		return "Socket is Busy";
	case NETWORK_ERRORS::SERVER_CANNOT_START:
		return "Server Cannot Start";
	case NETWORK_ERRORS::NETWORK_CODE_ERROR:
		return "Code is incorrect. Debug.";
	case NETWORK_ERRORS::UNKNOWN_ERROR:
		return "Unhandled Network Error";
	case NETWORK_ERRORS::NETWORK_OPTION_ERROR:
		return "Invalid option error";
	case NETWORK_ERRORS::ADDRESS_ERROR:
		return "Address is invalid";
	default:
		return "Unknown Network Error ";
	}
}

void testing_utilities::network_utilities::exception_handle()
{
	system_utilities::print_messages();
	FAIL() << get_string_of_error(network::network_interface->get_status().error);
}

void testing_utilities::network_utilities::expect_exception(std::function<void()> function, NETWORK_ERRORS error)
{
	try
	{
		function();
	}
	catch(NetworkErrorException)
	{
		EXPECT_EQ(error, network::network_interface->get_status().error) << "The wrong error state was given";
		return;
	}
	system_utilities::print_messages();
	FAIL() << "Network Error Exception did not throw\nExpected " + get_string_of_error(error);
}

void testing_utilities::network_utilities::network_message_utilities::check_header(int message_id, int size, std::vector<unsigned char> p_message)
{
	EXPECT_EQ(0x65, p_message[0]) << "Invalid Packet Header";
	EXPECT_EQ(message_id, p_message[1]) << "Incorrect Message Id";
	EXPECT_EQ(size, p_message[2]) << "Incorrect Packet Size";
}

void testing_utilities::network_utilities::network_message_utilities::compare_messages(Unpacked_Message b, Network_Message p)
{
	if(p.size() != b.get_message().size())
	{
		FAIL() << "Body sizes are not the same";
		return;
	}
	for(int i = 0; i < p.number_of_fields(); i++)
	{
		std::string types = str_type(p[i]);
		if(types == typeid(Network_Address).name())
		{
			IPV4_Addr p_addr = dynamic_cast<Network_Address*>(&p[i])->get_data();
			IPV4_Addr b_addr = dynamic_cast<Network_Address*>(&b.get_message()[i])->get_data();
			if(p_addr == b_addr)
			{
				SUCCEED();
			}
			else
			{
				FAIL() << "Addresses in position " << i << " are not the same\n" << p_addr.get_as_string() << " vs " << b_addr.get_as_string();
			}
		}
		else if(types == typeid(Network_String).name())
		{
			std::string p_str = dynamic_cast<Network_String*>(&p[i])->get_data().second;
			std::string b_str = dynamic_cast<Network_String*>(&b.get_message()[i])->get_data().second;
			EXPECT_EQ(p_str, b_str) << "String in position " << i << " are not the same";
			Byte p_length = dynamic_cast<Network_String*>(&p[i])->get_data().first;
			Byte b_length = dynamic_cast<Network_String*>(&b.get_message()[i])->get_data().first;
			EXPECT_EQ(p_length, b_length) << "Length value of String in position " << i << " are not the same";
		}
		else if(types == typeid(Network_Bool).name())
		{
			bool p_str = dynamic_cast<Network_Bool*>(&p[i])->get_data();
			bool b_str = dynamic_cast<Network_Bool*>(&b.get_message()[i])->get_data();
			EXPECT_EQ(p_str, b_str) << "Boolean in position " << i << " are not the same";
		}
		else if(types == typeid(Network_Byte).name())
		{
			Byte p_str = dynamic_cast<Network_Byte*>(&p[i])->get_data();
			Byte b_str = dynamic_cast<Network_Byte*>(&b.get_message()[i])->get_data();
			EXPECT_EQ(p_str, b_str) << "Byte in position " << i << " are not the same";
		}
		else if(types == typeid(Network_Percent).name())
		{
			float p_str = dynamic_cast<Network_Percent*>(&p[i])->get_data();
			float b_str = dynamic_cast<Network_Percent*>(&b.get_message()[i])->get_data();
			EXPECT_EQ(p_str, b_str) << "Percent in position " << i << " are not the same";
		}
		else if(types == typeid(Network_Word).name())
		{
			short p_str = dynamic_cast<Network_Word*>(&p[i])->get_data();
			short b_str = dynamic_cast<Network_Word*>(&b.get_message()[i])->get_data();
			EXPECT_EQ(p_str, b_str) << "Word in position " << i << " are not the same";
		}
		else
		{
			FAIL() << "Type " + types + " is not handled by test";
		}
	}
}

void testing_utilities::network_utilities::network_message_utilities::compare_messages(Packed_Message p, Network_Message m)
{
	if(p.size() != m.size() + sizeof(Message_Header) + sizeof(Message_Footer))
	{
		FAIL() << "Message sizes are not the same";
		return;
	}
	int current_position = sizeof(Message_Header);
	for(int i = 0; i < m.number_of_fields(); i++)
	{
		std::string types = str_type(m[i]);
		if(types == typeid(Network_Address).name())
		{
			system_utilities::testing_messges->push(System_Message(MESSAGE_PRIORITY::DEBUG_MESSAGE, "Address found at byte " + std::to_string(current_position), "Packed message compare"));
			IPV4_Addr p_addr = dynamic_cast<Network_Address*>(&m[i])->get_data();
			for(int j = 0; j < sizeof(IPV4_Addr); j++)
			{
				EXPECT_EQ(p.get_packet()[current_position], p_addr.get_addr_bytes()[j]) << "Address at byte " << current_position << " for field " << i << " are not the same\n";
				current_position++;
			}
		}
		else if(types == typeid(Network_String).name())
		{
			system_utilities::testing_messges->push(System_Message(MESSAGE_PRIORITY::DEBUG_MESSAGE, "String found at byte " + std::to_string(current_position), "Packed message compare"));
			Byte p_length = dynamic_cast<Network_String*>(&m[i])->get_data().first;
			EXPECT_EQ(p_length, p.get_packet()[current_position]) << "Length value of String at byte " << current_position << " for field " << i << " are not the same";
			current_position++;
			std::string p_str = dynamic_cast<Network_String*>(&m[i])->get_data().second;
			for(int j = 0; j < p_str.size(); j++)
			{
				EXPECT_EQ(p.get_packet()[current_position], p_str[j]) << "Character at byte " << current_position << " for field " << i << " are not the same";
				current_position++;
			}
		}
		else if(types == typeid(Network_Bool).name())
		{
			system_utilities::testing_messges->push(System_Message(MESSAGE_PRIORITY::DEBUG_MESSAGE, "Bool found at byte " + std::to_string(current_position), "Packed message compare"));
			bool p_bool = dynamic_cast<Network_Bool*>(&m[i])->get_data();
			EXPECT_EQ(p_bool, p.get_packet()[current_position]) << "Boolean at byte " << current_position << " for field " << i << " are not the same";
			current_position++;
		}
		else if(types == typeid(Network_Byte).name())
		{
			system_utilities::testing_messges->push(System_Message(MESSAGE_PRIORITY::DEBUG_MESSAGE, "Byte found at byte " + std::to_string(current_position), "Packed message compare"));
			Byte p_byte = dynamic_cast<Network_Byte*>(&m[i])->get_data();
			EXPECT_EQ(p_byte, p.get_packet()[current_position]) << "Byte at byte " << current_position << " for field " << i << " are not the same";
			current_position++;
		}
		else if(types == typeid(Network_Percent).name())
		{
			system_utilities::testing_messges->push(System_Message(MESSAGE_PRIORITY::DEBUG_MESSAGE, "Percent found at byte " + std::to_string(current_position), "Packed message compare"));
			float p_per = dynamic_cast<Network_Percent*>(&m[i])->get_data();
			float s_per = p.get_packet()[current_position];
			current_position++;
			s_per += p.get_packet()[current_position] / 100.0;
			EXPECT_EQ(p_per, s_per) << "Percent in position " << i << " are not the same";
			current_position++;
		}
		else if(types == typeid(Network_Word).name())
		{
			system_utilities::testing_messges->push(System_Message(MESSAGE_PRIORITY::DEBUG_MESSAGE, "Word found at byte " + std::to_string(current_position), "Packed message compare"));
			short number = short(((p.get_packet()[current_position] << 8) & 0xff00) | (p.get_packet()[current_position + 1] & 0xff));
			short p_str = dynamic_cast<Network_Word*>(&m[i])->get_data();
			EXPECT_EQ(number, p_str) << "Word in position " << i << " are not the same";
			current_position += 2;
		}
		else
		{
			FAIL() << "Type " + types + " is not handled by test";
		}
	}
}

void testing_utilities::network_utilities::network_message_utilities::compare_header(Packed_Message p, Unpacked_Message u)
{
	EXPECT_EQ(p.get_packet()[0], u.get_header().message_start);
	EXPECT_EQ(p.get_packet()[1], static_cast<Byte>(u.get_header().message_id));
	EXPECT_EQ(p.get_packet()[2], u.get_header().length);
}

void testing_utilities::network_utilities::network_message_utilities::compare_footer(Packed_Message p, Unpacked_Message u)
{
	Byte sum_byte_1_index = p.size() - 2;
	Byte sum_byte_2_index = p.size() - 1;

	EXPECT_EQ(p.get_packet()[sum_byte_1_index], u.get_footer().chk1);
	EXPECT_EQ(p.get_packet()[sum_byte_2_index], u.get_footer().chk2);
}

void testing_utilities::subsystem_utilities::model_utilities::check_is_running(bool is_running)
{
	EXPECT_EQ(model::model_running, is_running);
}

void testing_utilities::error_utilities::check_override_failure(std::function<void()> function)
{
	try
	{
		function();
	}
	catch(UnimplementedFunctionException)
	{
		SUCCEED();
		return;
	}
	catch(...)
	{
		FAIL() << "Wrong exception thrown";
	}
	FAIL() << "No exception thrown";
}