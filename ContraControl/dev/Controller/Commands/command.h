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
	
	double time_to_complete = 0.0;
	Command() { };
	~Command() {};
	virtual COMMAND_ID get_unique_id() { return COMMAND_ID::INVALID; };
private:
};

#endif // !COMMAND_H