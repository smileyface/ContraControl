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
bool system_setup = false;
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
	setup_messaging();
	LOG_INFO("Initalizing System", "Test");
	if(system_setup == false)
	{
		try
		{
			system_utilities::network_utilities::setup();
		}
		catch(NetworkErrorException)
		{
			LOG_ERROR("Network Error Caught", "Test");
			testing_utilities::network_utilities::exception_handle();
		}
		system_setup = true;
	}
	print_log_messages();
}

void system_utilities::setup_messaging()
{
	testing_utilities::message_utilities::setup_testing();
	if(message_consumer == 0)
	{
		message_consumer = Message_Relay::get_instance()->register_consumer<Logging_Message>();
	}
}

void system_utilities::teardown_messaging()
{
	testing_utilities::message_utilities::messaging_teardown();
	print_log_messages();
	Message_Relay::get_instance()->deregister_consumer(message_consumer);
	testing_utilities::message_utilities::system_is_clean();
	Message_Relay::destroy_instance();
	message_consumer = 0;
}

void system_utilities::start_system()
{
	LOG_INFO("Starting Loops", "Test");
	model->start_loop();
	controller->start_loop();
	view->start_loop();
	print_log_messages();
}

void system_utilities::stop_system()
{
	model->stop_loop();
	controller->stop_loop();
	view->stop_loop();
}

static void display_log_messages(Logging_Message mess)
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
	LOG_INFO("System Teardown", "Test");
	Scheduler::destroy_instance();
	Controller::destroy_instance();
	Model::destroy_instance();
	View::destroy_instance();
	network::clean_up();
	teardown_messaging();
	system_setup = false;
}

void system_utilities::step(int steps)
{
	std::chrono::milliseconds frameDurationMs(100);
	for(int i = 0; i < steps; i++)
	{
		Scheduler::get_instance()->frame(frameDurationMs);
	}
	print_log_messages();
}

void system_utilities::run_all_queued_commands()
{
	std::chrono::milliseconds frameDurationMs(100);
	while(Commander::get_instance()->get_number_of_commands() > 0)
	{
		Scheduler::get_instance()->frame(frameDurationMs);
	}
	print_log_messages();
}
void system_utilities::sleep_thread(int time_to_sleep)
{
		std::this_thread::sleep_for(std::chrono::milliseconds(time_to_sleep));
}

void system_utilities::model_utilities::start()
{
	model->start_loop();
}

void system_utilities::model_utilities::stop()
{
	model->stop_loop();
}

void system_utilities::controller_utilities::start()
{
	controller->start_loop();
}

void system_utilities::controller_utilities::stop()
{
	controller->stop_loop();
}

void system_utilities::network_utilities::setup()
{
	try
	{
		std::string i;
		if(std::getenv("CI") != NULL)
		{
			CI = true;
			LOG_INFO("On a CI machine", "Test Setup");
		#ifdef __linux__
			network::initalize("nat");
		#endif // __linux
		#ifdef _WIN32
			network::initalize("vEthernet (nat)");
		#endif
		}
		else
		{
			LOG_INFO("Not on a CI machine", "Test Setup");
			network::initalize();
		}
	}
	catch(NetworkErrorException e)
	{
		testing_utilities::network_utilities::exception_handle();
	}
}

bool system_utilities::keyboard_utilities::connect = true;
