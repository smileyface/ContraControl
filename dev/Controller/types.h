#ifndef CONTROLLER_TYPES_H
#define CONTROLLER_TYPES_H

#include "../Model/types.h"

#include "Commands/command.h"


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
#endif // !CONTROLLER_TYPES_H