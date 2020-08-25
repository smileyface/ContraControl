#ifndef COMMAND_MODEL_INTERFACE
#define COMMAND_MODEL_INTERFACE

#include "types.h"

namespace model_interfaces {
	namespace controller_interface {

		void add_to_step(Model_Command theCommand);
		void request_command(Model_Command theCommand, double seconds_to_execute);
		Command* get_command_object(COMMAND_ID Command, std::string args);
	}
}

#endif // !MODEL_COMMAND_INTERFACE