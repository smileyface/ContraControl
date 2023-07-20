#include <thread>
#include <chrono>
#include <iostream>

#include "system_utilities.h"

#include "Utilities/exceptions.h"
#include "test_utilities.h"

#include "../../dev/Model/model_main.h"
#include "../../dev/Controller/controller_main.h"

#include "../../Network/network_main.h"
#ifdef _WIN32
#include <Windows.h>
#include "../../Network/system_interfaces/windows_network_interface.h"
#endif // _WIN32
#ifdef __linux__
#include "../../Network/system_interfaces/linux_network_interface.h"
#endif

Message_Consumer* message_consumer = 0;
bool stale;

bool system_utilities::CI = false;
#ifdef _WIN32
bool system_utilities::LINUX = false;
bool system_utilities::WINDOWS = true;
#endif
#ifdef __linux__
bool system_utilities::LINUX = true;
bool system_utilities::WINDOWS = false;
#endif

void system_utilities::setup()
{
	try
	{
		model::initalize();
		controller::initalize();
	}
	catch(NetworkErrorException)
	{
		printf("Caught network exception");
		testing_utilities::network_utilities::exception_handle();
	}
	setup_messaging();
}

void system_utilities::setup_messaging()
{
	if(message_consumer == 0)
	{
		message_consumer = Message_Relay::get_instance()->register_consumer<Logging_Message>();
	}
}

void system_utilities::teardown_messaging()
{
	print_log_messages();
	Message_Relay::get_instance()->deregister_consumer(message_consumer);
	Message_Relay::get_instance()->clear();
	message_consumer = 0;
}

void display_log_messages(Logging_Message mess)
{
	int level = (int) MESSAGE_PRIORITY::INFO_MESSAGE;
#ifdef DEBUG
	level = (int) MESSAGE_PRIORITY::DEBUG_MESSAGE;
#endif // DEBUG

	if((int) mess.get_priority() < level)
	{
		return;
	}
	std::string priority_string;
	if(mess.get_priority() == MESSAGE_PRIORITY::ERROR_MESSAGE)
	{
		std::cout << "[  \u001b[33m" + mess.get_priority_string() + "\u001b[0m   ]";
	}
	else if(mess.get_priority() == MESSAGE_PRIORITY::INFO_MESSAGE)
	{
		std::cout << "[  " + mess.get_priority_string() + "    ]";
	}
	else
	{
		std::cout << "[  " << mess.get_priority_string() << "   ]";
	}
	std::cout << " (" << mess.get_location() << ")  " << mess.get_message() << std::endl << std::flush;
}

void system_utilities::print_log_messages()
{
	for(auto message = Message_Relay::get_instance()->pop<Logging_Message>(message_consumer); message.is_valid() == true; message = Message_Relay::get_instance()->pop<Logging_Message>(message_consumer))
	{
		display_log_messages(message);
	}
}

void system_utilities::cleanup()
{
	controller::clean_up();
	model::clean_up();
	teardown_messaging();
}

void system_utilities::step(int steps)
{
	for(int i = 0; i < steps; i++)
	{
		controller::step();
		model::step();
	}
}

void system_utilities::sleep_thread(int time_to_sleep)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(time_to_sleep));
}

void system_utilities::model_utilities::start()
{
	model::start_loop();
}

void system_utilities::model_utilities::stop()
{
	model::stop_loop();
}

void system_utilities::controller_utilities::start()
{
	controller::start_controller();
}

void system_utilities::controller_utilities::stop()
{
	controller::stop_controller();
}

void system_utilities::network_utilities::setup()
{
	try
	{
		system_utilities::setup();
		std::string i;
		if(std::getenv("CI") != NULL)
		{
			CI = true;
			LOG_INFO("On a CI machine", "Test Setup");
		#ifdef __linux__
			network::init_network_interfaces("nat");
		#endif // __linux
		#ifdef _WIN32
			network::init_network_interfaces("vEthernet (nat)");
		#endif
		}
		else
		{
			LOG_INFO("Not on a CI machine", "Test Setup");
			network::init_network_interfaces();
		}
	}
	catch(NetworkErrorException e)
	{
		testing_utilities::network_utilities::exception_handle();
	}
}

bool system_utilities::keyboard_utilities::connect = true;
