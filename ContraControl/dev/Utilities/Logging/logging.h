#ifndef CC_LOGGING_MAIN_H
#define CC_LOGGING_MAIN_H


#include <vector>
#include "log_item.h"
class Logger {
public:
	/* Static access method. */
	static Logger* getInstance();

	void addItem(LOG_PRIORITY priority, std::string msg, std::string  device);
private:
	Logger() {};
	static Logger* instance;
	std::vector<LogItem> logging;
};
/* Null, because instance will be initialized on demand. */


namespace sys_log {
	void log(LOG_PRIORITY priority, std::string msg, std::string  device);
};


#endif // !LOGGING_MAIN_H