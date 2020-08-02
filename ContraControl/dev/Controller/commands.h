#ifndef COMMANDS_INCLUSION_H
#define COMMANDS_INCLUSION_H

#include "Commands/command.h"
#include "Commands/initalize.h"
#include "Commands/on.h"
#include "Commands/Off.h"

typedef std::pair<uint16_t, Command> Device_Command;
typedef std::pair<double, Device_Command> Timed_Command;


#endif // !COMMANDS_INCLUSION_H