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
	logging.emplace_back(Log_Entry(priority, msg, device));
}

Log_Entry Logger::pop()
{
	Log_Entry item = logging.front();
	logging.pop_front();
	return item;
}

Log_Entry Logger::drop()
{
	Log_Entry item = logging.back();
	logging.pop_back();
	return Log_Entry();
}

void sys_log::log(LOG_PRIORITY priority, std::string msg, std::string device)
{
	Logger* log = Logger::getInstance();
	log->addItem(priority, msg, device);
}
Log_Entry sys_log::pop()
{
	Logger* log = Logger::getInstance();
	return log->pop();
}

Log_Entry sys_log::drop()
{
	Logger* log = Logger::getInstance();
	return log->drop();
}

