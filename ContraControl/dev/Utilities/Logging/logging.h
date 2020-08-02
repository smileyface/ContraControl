#ifndef CC_LOGGING_MAIN_H
#define CC_LOGGING_MAIN_H


#include <vector>
#include "log_item.h"
class logger {
public:
	std::vector<LogItem> logging;
};

static logger _log;

#endif // !LOGGING_MAIN_H