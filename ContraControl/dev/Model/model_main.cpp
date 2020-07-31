#include "model_main.h"
void model::loop() {

}

void model::read_program()
{
	known_devices["Device_1"] = SwitchDevice();
}

void model::initalize() {
	map<string, Device>::iterator it;
	for (it = known_devices.begin; it != known_devices.end; it++) {
		it->second.run_command(DEVICE_COMMAND::INITALIZE);
	}
}