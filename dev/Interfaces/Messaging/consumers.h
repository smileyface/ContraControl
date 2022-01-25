#ifndef MESSAGE_CONSUMER_H
#define MESSAGE_CONSUMER_H

#include <vector>
struct Message_Consumer
{
	Message_Consumer(bool& stale);
	void notify();
	void freshen();

private:
	bool* stale;
};

typedef std::vector<Message_Consumer*> Consumer_List;
#endif
