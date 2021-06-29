/*****************************************************************//**
 * \file   off.h
 * \brief  
 * 
 * \author kason
 * \date   April 2021
 *********************************************************************/
#ifndef OFF_COMMAND
#define OFF_COMMAND

#include "../command.h"

 /**
  * A command to turn devices off.
  */
class Off : public Command {
public:
 
	Off() {};
	~Off() {};
	virtual COMMAND_ENUM get_id() { return COMMAND_ENUM::OFF; }

};

#endif // !OFF_COMMAND
