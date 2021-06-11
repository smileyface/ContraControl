#ifndef MODEL_CHANNEL_STATE
#define MODEL_CHANNEL_STATE

#include "state.h"

typedef unsigned char Channel;

const Channel INVALID_POSITION = -1;

struct Channel_State : Device_State
{
	bool transitioning;
	std::vector<Channel> channels;

	Channel_State() { transitioning = false; }
	Channel_State(Device_State _state)
	{
		this->power = _state.power;
		this->initalized = _state.initalized;
		this->valid = _state.valid;
	}
	Channel get_position()
	{
		return channels[0];
	}
	Channel& get_position_ptr()
	{
		return channels[0];
	}
};


#endif // !MODEL_RGB_STATE