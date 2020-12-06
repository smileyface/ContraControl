#ifndef OFF_COMMAND
#define OFF_COMMAND

#include "../command.h"

class Off : public Command {
public:
 
	Off() {};
	~Off() {};
	virtual COMMAND_ENUM get_id() { return COMMAND_ENUM::OFF; }
    virtual void mangle_state(Device_State& state)
    {
        if(state.initalized == false)
        {
            state.valid = false;
            return;
        }
        state.power = false;
    }
};

#endif // !OFF_COMMAND
