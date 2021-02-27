#ifndef CONTROLLER_TYPES_H
#define CONTROLLER_TYPES_H

#include "../Model/types.h"

#include "Commands/command.h"


class Timed_Command {
public:
	Command* command;
	unsigned short device_id;
	double time;
	bool run;

	Timed_Command(Command* cmd, Device_Id dev, double t) {
		command = cmd;
		device_id = dev;
		time = t;
	};


};
#endif // !CONTROLLER_TYPES_H