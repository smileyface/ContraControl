#ifndef SYSTEM_TESTING_UTIL_H
#define SYSTEM_TESTING_UTIL_H

namespace system_utilities
{
	void setup();

	void cleanup();

	void step(int steps);
	namespace model_utilities
	{
		void start();
		void stop();
	}
}

#endif