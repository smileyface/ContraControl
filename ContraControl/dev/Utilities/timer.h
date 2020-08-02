#ifndef TIMER_H
#define TIMER_H

#include <ctime>

class Timer {
public:
	std::clock_t current_time = std::clock();
	double elapsed_time = 0.0;

	void update_time() {

		elapsed_time = (std::clock() - current_time) / (double)CLOCKS_PER_SEC;
	}
	double get_elapsed_time() { return elapsed_time; }
	void reset_clock() {
		elapsed_time = 0.0;
		current_time = std::clock();
	}
	void start_clock() {
		current_time = std::clock();
	}

	Timer() {};
	~Timer() {};
};

#endif // !TIMER_H