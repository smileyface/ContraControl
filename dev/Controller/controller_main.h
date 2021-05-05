/*****************************************************************//**
 * \file   controller_main.h
 * \brief  Main brains for the controller. DO NOT INCLUDE. Include a controller_interface instead.
 * 
 * \author kason
 * \date   April 2021
 *********************************************************************/


#ifndef MAIN_EXECUTOR_H
#define MAIN_EXECUTOR_H

#include "../Interfaces/types/timed_command.h"
#include "system/timer.h"

namespace controller
{
	extern bool controller_running;
	extern std::vector<Timed_Command> controller_queue;

	bool sort_pair(Timed_Command i, Timed_Command j);

	void initalize();
	void stop_controller();
	void add_command(Timed_Command tc);

	void step();

	void clean_up();
}



#endif