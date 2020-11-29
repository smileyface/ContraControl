#ifndef ON_COMMAND_H
#define ON_COMMAND_H


#include "../command.h"

class On : public Command {
public:
	On() {};
	~On() {};
	virtual COMMAND_ENUM get_id() { return COMMAND_ENUM::ON; }
    virtual void mangle_state(Device_State& state)
    {
        if(state.initalized == false)
        {
            state.valid = false;
            return;
        }
        state.power = true;
    }
};
#endif // !ON_COMMAND_H
