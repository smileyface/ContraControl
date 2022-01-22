#include "../Alerts/system_alerts.h"

#include <mutex>
#include <string>

std::mutex g_pages_mutex;

std::string alert_priority_as_string(ALERT_PRIORITY al)
{
	std::string level;
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
	return level;
}

Alert::Alert(ALERT_PRIORITY pri, std::string msg, std::string loc)
{
	priority = pri;
	message = msg;
	location = loc;
	valid_alert = true;
}

Alert::Alert(bool va)
{
	priority = ALERT_PRIORITY::INFO;
	message = "";
	location = "";
	valid_alert = va;
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
	if (list_of_alerts.size() == 0)
	{
		return Alert(false);
	}
	Alert grabbed_alert = list_of_alerts[0];
	std::lock_guard<std::mutex> guard(g_pages_mutex);
	list_of_alerts.erase(list_of_alerts.begin());
	return grabbed_alert;
}

System_Alerts* System_Alerts::get_instance()
{
	if (instance == nullptr)
	{
		instance = new System_Alerts();
	}
	return instance;
}
