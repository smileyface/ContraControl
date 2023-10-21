/*****************************************************************//**
 * \file   commands.h
 * \brief  A file to include to get all defined commands. To drop in a new command, you must add the command to here.
 * 
 * \author kason
 * \date   April 2021
 *********************************************************************/

#ifndef COMMANDS_INCLUSION_H
#define COMMANDS_INCLUSION_H

//commands.h included by inheritance
#include "commands/device/device_initalize.h"
//#include "commands/device/device_command.h"
#include "commands/device/device_create.h"
#include "commands/device/device_destruction.h"
#include "commands/device/on.h"
#include "commands/device/off.h"
#include "commands/device/assign.h"
//#include "commands/node/node_command.h"
#include "commands/node/node_create.h"
#include "commands/node/node_initalize.h"
#include "commands/node/node_destroy.h"
#include "commands/node/node_connect.h"
#include "commands/node/node_disconnect.h"

#endif // !COMMANDS_INCLUSION_H