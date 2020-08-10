#include"logging.h"


Logger* Logger::instance = 0;

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
};

void sys_log::log(LOG_PRIORITY priority, std::string msg, std::string device)
{
	Logger* log = Logger::getInstance();
	log->addItem(priority, msg, device);
};
