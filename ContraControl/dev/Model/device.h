
#ifndef MAIN_DEVICE_H
#define MAIN_DEVICE_H

#include <map>
#include<functional>

#include "../Controller/executor.h"

typedef uint8_t Command;
#define Command_Def static const Command
#define Command_Func [this]()

class DEVICE_COMMAND
{
public:
	Command_Def INITALIZE = 0;
	Command_Def INVALID = 255;
};

class Device
{
public:
	Device();
	void run_command(Command command);
	uint16_t get_id() { return id; };
	void setup_functions();
	void initalize();
protected:
	void add_command(Command, std::function<void()>);
	std::map<Command, std::function<void()>> commands;
	Command state = DEVICE_COMMAND::INVALID;
	uint16_t id = UINT16_MAX;
private:
	
};

#endif
