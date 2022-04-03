#ifndef SYSTEM_TESTING_UTIL_H
#define SYSTEM_TESTING_UTIL_H

namespace system_utilities
{
	void setup();

	void cleanup();
	void print_messages();

	void step(int steps);

	void sleep_thread(int wait_time);
	namespace model_utilities
	{
		void start();
		void stop();
	}
}

#endif