#ifndef MODEL_CONTROLLER_INTERFACE_H
#define MODEL_CONTROLLER_INTERFACE_H

#include "../types.h"
#include "../../Model/interfaces/types.h"

namespace controller_interfaces {
	namespace model_interface {
		//to model
		void send_command(Timed_Command timed_command);
		
		//from model
		void request_command_add(Timed_Command timed_command);
	}
}

#endif // !MODEL_CONTROLLER_INTERFACE_H

