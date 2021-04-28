#ifndef MODEL_MAIN_H
#define MODEL_MAIN_H

#include <map>
#include <vector>
#include <string>

#include "../Utilities/timer.h"
#include "system/timer.h"

#include "../Interfaces/types/model_command.h"
#include "../Interfaces/types/device_label.h"

namespace model {
	extern std::map<Node_Id, Node*> nodes;
	extern bool model_running;

	extern Node_Id my_node;

	extern std::vector<Model_Command> step_actions;

	Node* get_node(Node_Id);
	void create_node(Node_Type, Node_Id);

	Device* get_device(Device_Label);

	void initalize();

	void step();

	void add_command(Device_Label, Command*);


	void system_commands(Command*);

	void stop_loop();

	void clean_up();



}
#endif 