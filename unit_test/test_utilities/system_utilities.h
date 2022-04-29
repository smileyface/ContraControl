#ifndef SYSTEM_TESTING_UTIL_H
#define SYSTEM_TESTING_UTIL_H

#include "../../dev/Interfaces/Messaging/system_messaging.h"

#ifdef CI
const bool IS_CI = true;
#else
const bool IS_CI = false;
#endif // CI



namespace system_utilities
{
	void setup();
	void setup_messaging();

	void cleanup();
	void print_messages();

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
	extern System_Messages* testing_messges;
}

#endif