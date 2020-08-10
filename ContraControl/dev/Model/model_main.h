#ifndef MODEL_MAIN_H
#define MODEL_MAIN_H

#include <map>
#include <vector>
#include <string>

#include "devices.h"
#include "../Utilities/timer.h"


namespace model {
	class Model_Command {
	public:
		Model_Command(Device_Id id, Command* command);
		Device_Id id; 
		Command* command;
	};

	extern Timer timer;
	extern std::map<Device_Name, Device*> known_devices;
	extern bool model_running;

	extern std::vector<Model_Command> step_run;
	extern std::map<Device_Id, Device_Name> id_map;


	void initalize();
	void add_device(std::string name, Device *device);

	void add_to_step(Model_Command theCommand);
	void loop();

	void stop_loop();



}
#endif 