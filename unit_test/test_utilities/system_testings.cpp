#include "system_testings.h"

#include "../../dev/Model/model_main.h"
#include "../../dev/Controller/controller_main.h"


void system_utilities::setup()
{
	model::initalize();
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

void system_utilities::model_utilities::start()
{
	model::start_loop();
}

void system_utilities::model_utilities::stop()
{
	model::stop_loop();
}
