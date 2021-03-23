#ifndef INITALIZE_COMMAND_H
#define INITALIZE_COMMAND_H

#include "../command.h"
#include <string>

class Initalize : public Command
{
public:
	~Initalize() {};
	std::string name;
	virtual COMMAND_ENUM get_id() { return COMMAND_ENUM::INITALIZE; }
    virtual void mangle_state(Device_State& state)
    {
        state.initalized = true;
        state.valid = validity_check();
		state.position = 0.0f;
    }

	virtual bool validity_check()
	{
		return true;
	}
};
#endif // !INITALIZE_COMMAND_H