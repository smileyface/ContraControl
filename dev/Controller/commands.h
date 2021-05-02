/*****************************************************************//**
 * \file   commands.h
 * \brief  A file to include to get all defined commands. To drop in a new command, you must add the command to here.
 * 
 * \author kason
 * \date   April 2021
 *********************************************************************/

#ifndef COMMANDS_INCLUSION_H
#define COMMANDS_INCLUSION_H

//device.h included by inheritance
#include "Commands/common/initalize.h"
#include "Commands/device/on.h"
#include "Commands/device/off.h"
//transition.h included by inheritance
#include "Commands/device/transitions/linear_transition.h"




#endif // !COMMANDS_INCLUSION_H