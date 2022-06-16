#ifndef SYSTEM_TESTING_UTIL_H
#define SYSTEM_TESTING_UTIL_H

#include "../../dev/Interfaces/Messaging/system_messaging.h"

namespace system_utilities
{
	void setup();
	void setup_messaging();
	void teardown_messaging();

	void cleanup();
	void print_log_messages();

	void step(int steps);

	void sleep_thread(int wait_time);
	namespace model_utilities
	{
		void start();
		void stop();
	}
	namespace network_utilities
	{
		void setup();
	}
}

#endif