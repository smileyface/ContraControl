#ifndef TESTING_UTILITIES_H
#define TESTING_UTILITIES_H

#include "../../dev/Model/model_main.h"
#include "../../dev/Controller/controller_main.h"

namespace testing_util
{
	void log_top_test(Command* command, Device* device);
	void log_bottom_test(Command* command, Device* device);
	void get_partial_on(Command* command, Device* device, int timeout);
}
#endif