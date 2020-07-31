#include "device.h"


Device::Device()
{
	Device::commands[DEVICE_COMMAND::INITALIZE] = Command_Func{
		state = DEVICE_COMMAND::INITALIZE;
	};
}


void Device::initalize()
{
	id = Executor::get_instance()->registerDevice();
	state = DEVICE_COMMAND::INITALIZE;
	
}

void Device::add_command(Command command, std::function<void()> func)
{
	commands[command] = func;
}

void Device::run_command(Command command)
{
	commands[command]();
}

