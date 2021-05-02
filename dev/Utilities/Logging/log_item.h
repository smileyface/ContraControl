#ifndef LOG_ITEM_H
#define LOG_ITEM_H

#include <string>
#include <vector>

#include "../timer.h"

enum class LOG_PRIORITY {
	SEVERE,
	INFO,
	DEBUG,
	ERROR
};
class LogItem
{
public:
	LogItem() {
		priority = LOG_PRIORITY::ERROR;
		message = "NO MESSAGE";
		device = "SYSTEM ERROR";
	}
	LogItem(LOG_PRIORITY pri, std::string msg, std::string dev)
	{
		priority = pri;
		message = msg;
		device = dev;
	};
	LOG_PRIORITY priority;
	std::string message;
	std::string device;
private:
	Timer timer;

};




#endif