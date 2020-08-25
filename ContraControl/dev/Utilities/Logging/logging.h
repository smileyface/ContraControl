#ifndef CC_LOGGING_MAIN_H
#define CC_LOGGING_MAIN_H


#include <queue>
#include "log_item.h"
#include "../../Controller/commands.h"
class Logger {
public:
	/* Static access method. */
	static Logger* getInstance();

	void addItem(LOG_PRIORITY priority, std::string msg, std::string  device);
	LogItem pop();
private:
	Logger();
	static Logger* instance;
	std::queue<LogItem> logging;
};


namespace sys_log {
	void log(LOG_PRIORITY priority, std::string msg, std::string  device);
	LogItem pop();
};




#endif // !LOGGING_MAIN_H