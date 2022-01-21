#include "..\Alerts\system_alerts.h"

#include <mutex>

std::mutex g_pages_mutex;

char* alert_priority_as_string(ALERT_PRIORITY al)
{
	switch (al)
	{
	case ALERT_PRIORITY::SEVERE:
		return "SEVERE";
	case ALERT_PRIORITY::INFO:
		return "INFO";
	case ALERT_PRIORITY::ERROR:
		return "ERROR";
	case ALERT_PRIORITY::DEBUG:
		return "DEBUG";
	default:
		return "UNHANDLED PRIORITY";
	}
	return "UNHANDLED PRIORITY";
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
