
#ifndef MAIN_EXECUTOR_H
#define MAIN_EXECUTOR_H

#include <vector>
#include <functional>

typedef  std::function<void()> func_ptr;
typedef  std::pair<int, func_ptr> timed_command;

enum TIMES : uint16_t
{
	NOW = 0
};

class Executor
{
public:
	static Executor* get_instance();
	uint16_t registerDevice();
private:

	Executor();
	static Executor* instance;

	uint16_t num_of_devices;
	std::vector<timed_command> commands;
};




#endif