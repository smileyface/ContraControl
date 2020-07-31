#include "executor.h"


Executor* Executor::instance = 0;

Executor::Executor()
{
	num_of_devices = 0;
}

uint16_t Executor::registerDevice() {
	return num_of_devices++;
}

Executor* Executor::get_instance()
{
	if (!Executor::instance)
		Executor::instance = new Executor();
	return Executor::instance;
}

