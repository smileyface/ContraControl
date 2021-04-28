#ifndef INTERFACE_TIMED_COMMAND_TYPE
#define INTERFACE_TIMED_COMMAND_TYPE

#include "../../Interfaces/types/device_label.h"
class Timed_Command {
public:
	Command* command;
	Device_Label device_label;
	double time;
	bool run;

	Timed_Command(Command* cmd, Device_Label label, double t) {
		command = cmd;
		device_label = label;
		time = t;
	};


};

#endif
