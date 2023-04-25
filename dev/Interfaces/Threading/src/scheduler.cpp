#include "../scheduler/scheduler.h"

Scheduler* Scheduler::instance = nullptr;

Scheduler* Scheduler::get_instance()
{
	if(instance == nullptr)
	{
		instance = new Scheduler();
	}
	return instance;
}

Scheduler::Scheduler() :
	refresh_rate(1 / 30)
{
	frame[FRAME_SOURCE::MAIN] = { .01, {} };
	frame[FRAME_SOURCE::CONTROL] = { .1, {} };
	frame[FRAME_SOURCE::MODEL] = { .1, {} };
	frame[FRAME_SOURCE::VIEW_SUBSYSTEM] = { .4, {} };
	frame[FRAME_SOURCE::MESSAGE_RELAY] = { .01, {} };
}
