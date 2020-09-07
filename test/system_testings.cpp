#include "pch.h"

#include "system_testings.h"

#include "../dev/Model/model_main.h"
#include "../dev/Controller/controller_main.h"


void system_util::setup()
{
	model::initalize();
	controller::initalize();
}

void system_util::cleanup() 
{
		controller::clean_up();
		model::clean_up();
}

void system_util::step(int steps)
{
	for (int i = 0; i < steps; i++)
	{
		controller::step();
		model::step();
	}
}