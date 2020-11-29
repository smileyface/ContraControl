#include "../basic/switch.h"
#include "../basic/gradient.h"

class Audio_Device : public Switch_Device
{
protected:
	struct Audio_State : public Device_State
	{
		double play_time;
	};

	Audio_State state;

	virtual void do_command(Command* command)
	{
		Switch_Device::do_command(command);
		switch (command->get_id())
		{
        case COMMAND_ENUM::INITALIZE:
            break;
		case COMMAND_ENUM::ON:
			state.play_time += model_timer.get_elapsed_time();
            break;
        case COMMAND_ENUM::OFF:
        case COMMAND_ENUM::TRANSITION:
        case COMMAND_ENUM::LINEAR_TRANSITION:
            break;
        case COMMAND_ENUM::INVALID:
            break;
            
		}


	};
};