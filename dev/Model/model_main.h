#ifndef MODEL_MAIN_H
#define MODEL_MAIN_H

#include <map>
#include <vector>
#include <string>

#include "node/node.h"
#include "../Utilities/timer.h"
#include "types.h"
#include "system/timer.h"


namespace model {
	extern std::map<Node_Id, Node*> nodes;
	extern bool model_running;

	extern std::vector<Model_Command> step_actions;
	extern std::map<Device_Id, Device_Name> id_map;

	Node* get_node(Node_Id);
	void create_node(Node_Type, Node_Id);

	Device* get_device(Device_Label);

	void initalize();

	void step();

	/*
	Return: array of run commands
	*/
	std::vector<int> run_commands();


	void system_commands(Command* command);

	void stop_loop();

	void clean_up();



}
#endif 