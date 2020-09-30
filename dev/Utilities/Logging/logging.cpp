#include"logging.h"


Logger* Logger::instance = 0;

Logger::Logger() {}

Logger* Logger::getInstance()
{
	if (instance == 0)
	{
		instance = new Logger();
	}

	return instance;
}
void Logger::addItem(LOG_PRIORITY priority, std::string msg, std::string device)
{
	logging.emplace_back(LogItem(priority, msg, device));
}

LogItem Logger::pop()
{
	LogItem item = logging.front();
	logging.pop_front();
	return item;
}

LogItem Logger::drop()
{
	LogItem item = logging.back();
	logging.pop_back();
	return LogItem();
}

void sys_log::log(LOG_PRIORITY priority, std::string msg, std::string device)
{
	Logger* log = Logger::getInstance();
	log->addItem(priority, msg, device);
}
LogItem sys_log::pop()
{
	Logger* log = Logger::getInstance();
	return log->pop();
}

LogItem sys_log::drop()
{
	Logger* log = Logger::getInstance();
	return log->drop();
}

