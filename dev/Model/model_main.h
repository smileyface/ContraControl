#ifndef MODEL_MAIN_H
#define MODEL_MAIN_H

#include <map>
#include <vector>
#include <string>

#include "device.h"
#include "../Utilities/timer.h"
#include "types.h"


namespace model {
	extern Timer timer;
	extern std::map<Device_Name, Device*> known_devices;
	extern bool model_running;

	extern std::vector<Model_Command> step_actions;
	extern std::map<Device_Id, Device_Name> id_map;

	Device* get_device(Device_Id device_id);

	void initalize();
	void add_device(std::string name, Device *device);

	void step();

	void stop_loop();

	void clean_up();



}
#endif 