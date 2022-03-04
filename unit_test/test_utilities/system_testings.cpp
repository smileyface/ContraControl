#include <thread>
#include <chrono> 

#include "system_testings.h"

#include "Utilities/exceptions.h"
#include "test_utilities.h"

#include "../../dev/Model/model_main.h"
#include "../../dev/Controller/controller_main.h"


void system_utilities::setup()
{
	try
	{
		model::initalize();
	}
	catch (NetworkErrorException)
	{
		printf("Caught network exception");
		testing_utilities::network_utilities::exception_handle();
	}
	catch (-1)
	{

	}
	controller::initalize();
}

void system_utilities::cleanup() 
{
		controller::clean_up();
		model::clean_up();
}

void system_utilities::step(int steps)
{
	for (int i = 0; i < steps; i++)
	{
		controller::step();
		model::step();
	}
}

void system_utilities::sleep_thread(int time_to_sleep)
{
	std::this_thread::sleep_for(std::chrono::seconds(time_to_sleep));
}

void system_utilities::model_utilities::start()
{
	model::start_loop();
}

void system_utilities::model_utilities::stop()
{
	model::stop_loop();
}
