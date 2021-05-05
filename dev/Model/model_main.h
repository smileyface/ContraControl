/*****************************************************************//**
 * \file   model_main.h
 * \brief  Main brains for the model. DO NOT INCLUDE. Include a model_interface instead
 * 
 * \author kason
 * \date   May 2021
 *********************************************************************/

#ifndef MODEL_MAIN_H
#define MODEL_MAIN_H

#include "system/timer.h"

#include "../Interfaces/types/model_command.h"

namespace model {
	extern Node_Map nodes;
	extern bool model_running;

	extern Node_Id my_node;

	extern std::vector<Model_Command> step_actions;

	Node* get_node(Node_Id);
	void create_node(Node_Type, Node_Id);

	Device* get_device(Device_Label);

	void initalize();

	void step();


	void stop_loop();

	void clean_up();
}
#endif 