#ifndef COMMAND_H
#define COMMAND_H


enum class COMMAND_ID :uint16_t
{
	INITALIZE,
	ON,
	OFF,
	INVALID = UINT16_MAX
};

class Command {
public:
	const static COMMAND_ID unique_id = COMMAND_ID::INVALID;
	double time_to_complete = 0.0;
	Command() {};
	~Command() {};
};

#endif // !COMMAND_H