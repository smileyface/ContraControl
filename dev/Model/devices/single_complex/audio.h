#include "../basic/switch.h"
#include "../basic/gradient.h"

class Audio_Device : public Switch_Device
{
protected:
	struct audio_state : public device_state
	{
		double play_time;
	};

	audio_state state;

	virtual void do_command(Command* command)
	{
		Switch_Device::do_command(command);
		switch (command->get_id())
		{
		case COMMAND_ENUM::ON:
			state.play_time += model_timer.get_elapsed_time();
		}


	};
};