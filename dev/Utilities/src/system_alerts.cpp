#include "../Alerts/system_alerts.h"

#include <algorithm>
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
	list_of_alerts.emplace_back(std::make_pair(alert, list_of_registered_consumers));
}

bool remove_func(std::pair<Alert, Consumer_List> Alert_Data)
{
	return Alert_Data.second.size() == 0;
}

std::vector<Alert> System_Alerts::pop(Message_Consumer* consumer)
{
	std::vector<Alert> list_of_captured_alerts;
	for (int i = 0; i < list_of_alerts.size(); i++)
	{
		auto it = std::find(list_of_alerts[i].second.begin(), list_of_alerts[i].second.end(), consumer);

		if (it != list_of_alerts[i].second.end())
		{
			list_of_captured_alerts.push_back(list_of_alerts[i].first);
			list_of_alerts[i].second.erase(it);
			
		}
	}
	
	auto it = std::remove_if(list_of_alerts.begin(), list_of_alerts.end(), remove_func);
	list_of_alerts.erase(it, list_of_alerts.end());
	return list_of_captured_alerts;
}

void System_Alerts::register_consumer(Message_Consumer* mc)
{
	list_of_registered_consumers.push_back(mc);
	for (int i = 0; i < list_of_alerts.size(); i++)
	{
		list_of_alerts[i].second.push_back(mc);
	}
}

System_Alerts* System_Alerts::get_instance()
{
	if (instance == nullptr)
	{
		instance = new System_Alerts();
	}
	return instance;
}
