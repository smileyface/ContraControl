#include "../Alerts/system_alerts.h"

#include <mutex>
#include <string>

std::mutex g_pages_mutex;

char* alert_priority_as_string(ALERT_PRIORITY al)
{
	std::string level;
	switch (al)
	{
	case ALERT_PRIORITY::SEVERE:
		level = "SEVERE";
	case ALERT_PRIORITY::INFO:
		level = "INFO";
	case ALERT_PRIORITY::ERROR:
		level = "ERROR";
	case ALERT_PRIORITY::DEBUG:
		level = "DEBUG";
	default:
		level = "UNHANDLED PRIORITY";
	}
	return &level[0];
}

System_Alerts* System_Alerts::instance;

System_Alerts::System_Alerts()
{
}

void System_Alerts::push(Alert alert)
{
	std::lock_guard<std::mutex> guard(g_pages_mutex);
	list_of_alerts.emplace_back(alert);
}

Alert System_Alerts::pop()
{
	Alert grabbed_alert = list_of_alerts[0];
	std::lock_guard<std::mutex> guard(g_pages_mutex);
	list_of_alerts.erase(list_of_alerts.begin());
	return list_of_alerts[0];
}

System_Alerts* System_Alerts::get_instance()
{
	if (instance == nullptr)
	{
		instance = new System_Alerts();
	}
	return instance;
}
