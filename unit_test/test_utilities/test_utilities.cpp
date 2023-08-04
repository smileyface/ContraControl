#include "test_utilities.h"
#include "system_utilities.h"

#include "../../Network/network_main.h"

#include "pch.h"

#include <typeinfo>

const int TIMEOUT_TIME = 5;

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
	system_utilities::print_log_messages();
	FAIL() << get_string_of_error(network::network_interface->get_status().error);
}

void testing_utilities::network_utilities::expect_exception(std::function<void()> function, NETWORK_ERRORS error)
{
	try
	{
		function();
	}
	catch(NetworkErrorException e)
	{
		EXPECT_STREQ(e.what(), "Network Error");
		EXPECT_EQ(error, network::network_interface->get_status().error) << "The wrong error state was given";
		return;
	}
	system_utilities::print_log_messages();
	FAIL() << "Network Error Exception did not throw\nExpected " + get_string_of_error(error);
}

void testing_utilities::network_utilities::network_message_utilities::check_header(int message_id, int size, std::vector<unsigned char> p_message)
{
	EXPECT_EQ(0x65, p_message[0]) << "Invalid Packet Header";
	EXPECT_EQ(message_id, p_message[1]) << "Incorrect Message Id";
	EXPECT_EQ(size, p_message[2]) << "Incorrect Packet Size";
}

void testing_utilities::network_utilities::network_message_utilities::compare_messages(Packed_Message m1, Packed_Message m2)
{
	Message_Header p_header, b_header;
	Network_Message p_body, b_body;
	Message_Footer p_footer, b_footer;
	m1.get_message(p_header, p_body, p_footer);
	m2.get_message(b_header, b_body, b_footer);
	if(p_body.size() != b_body.size())
	{
		FAIL() << "Body sizes are not the same";
		return;
	}
	for(int i = 0; i < p_body.get_message().size(); i++)
	{
		if(typeid(p_body[i]) == typeid(Network_Address))
		{
			IPV4_Addr p_addr = dynamic_cast<Network_Address*>(&p_body[i])->get_data();
			IPV4_Addr b_addr = dynamic_cast<Network_Address*>(&b_body[i])->get_data();
			if(p_addr == b_addr)
			{
				SUCCEED();
			}
			else
			{
				FAIL() << "Addresses in position " << i << " are not the same\n" << p_addr.get_as_string() << " vs " << b_addr.get_as_string();
			}
		}
		else if(typeid(p_body[i]) == typeid(Network_String))
		{
			std::string p_str = dynamic_cast<Network_String*>(&p_body[i])->get_data().second;
			std::string b_str = dynamic_cast<Network_String*>(&b_body[i])->get_data().second;
			EXPECT_EQ(p_str, b_str) << "String in position" << i << "are not the same";
			Byte p_length = dynamic_cast<Network_String*>(&p_body[i])->get_data().first;
			Byte b_length = dynamic_cast<Network_String*>(&b_body[i])->get_data().first;
			EXPECT_EQ(p_length, b_length) << "Length value of String in position" << i << "are not the same";
		}
		else if(typeid(p_body[i]) == typeid(Network_Bool))
		{
			bool p_str = dynamic_cast<Network_Bool*>(&p_body[i])->get_data();
			bool b_str = dynamic_cast<Network_Bool*>(&b_body[i])->get_data();
			EXPECT_EQ(p_str, b_str) << "Boolean in position" << i << "are not the same";
		}
		else if(typeid(p_body[i]) == typeid(Network_Byte))
		{
			Byte p_str = dynamic_cast<Network_Byte*>(&p_body[i])->get_data();
			Byte b_str = dynamic_cast<Network_Byte*>(&b_body[i])->get_data();
			EXPECT_EQ(p_str, b_str) << "Byte in position" << i << "are not the same";
		}
		else if(typeid(p_body[i]) == typeid(Network_Percent))
		{
			float p_str = dynamic_cast<Network_Percent*>(&p_body[i])->get_data();
			float b_str = dynamic_cast<Network_Percent*>(&b_body[i])->get_data();
			EXPECT_EQ(p_str, b_str) << "Percent in position" << i << "are not the same";
		}
		else if(typeid(p_body[i]) == typeid(Network_Word))
		{
			short p_str = dynamic_cast<Network_Word*>(&p_body[i])->get_data();
			short b_str = dynamic_cast<Network_Word*>(&b_body[i])->get_data();
			EXPECT_EQ(p_str, b_str) << "Word in position" << i << "are not the same";
		}
		else
		{
			FAIL() << "Type is not handled by test";
		}
	}
}

void testing_utilities::subsystem_utilities::model_utilities::check_is_running(bool is_running)
{
	EXPECT_EQ(model::model_running, is_running);
}

void testing_utilities::subsystem_utilities::controller_utilities::check_is_running(bool is_running)
{
	EXPECT_EQ(controller::controller_running, is_running);
}

void testing_utilities::error_utilities::check_override_failure(std::function<void()> function)
{
	try
	{
		function();
	}
	catch(UnimplementedFunctionException e)
	{
		EXPECT_STREQ(e.what(), "Function not implemented");
		SUCCEED();
		return;
	}
	catch(...)
	{
		FAIL() << "Wrong exception thrown";
	}
	FAIL() << "No exception thrown";
}


void dummy_func()
{ }

void testing_utilities::input_utilities::wait_for_keypress(KPI key)
{
	bool is_pressed = false;

	//buffer.keyboard->set_on_press(key, [&is_pressed] () mutable
	//							  {
	//								  is_pressed = true;
	//							  });

	//int sleep_time = 0;
	//if(!is_pressed && sleep_time < TIMEOUT_TIME)
	//{
	//	//try to push the button ourselves
	//	system_utilities::keyboard_utilities::press_button(get_char_from_kpi(key));
	//	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	//	sleep_time++;
	//}

	EXPECT_TRUE(is_pressed);
}

void testing_utilities::input_utilities::connect_keyboard(std::string path_to_keyboard)
{
	//buffer.keyboard->connect_to_keyboard();
}

void testing_utilities::message_utilities::system_is_clean()
{
	EXPECT_EQ(Message_Relay::get_instance()->number_of_consumers(), 0) << "There are still consumers on the Message Relay";
}
