#ifndef SYSTEM_ALERTS_UTILITY_H
#define SYSTEM_ALERTS_UTILITY_H

#include <vector>
#include <string>

/**
 Level of the alert.
 */
enum class ALERT_PRIORITY {
	/**
	A program breaking error.
	*/
	SEVERE,
	/**
	Informational alert. For verbose logging.
	*/
	INFO,
	/**
	Debug alert. For very verbose logging.
	*/
	DEBUG,
	/**
	A non-program stopping error.
	*/
	ERROR
};

std::string alert_priority_as_string(ALERT_PRIORITY al);


struct Alert
{
	ALERT_PRIORITY priority;
	std::string message;
	std::string location;
	bool valid_alert;
	Alert(ALERT_PRIORITY pri, std::string msg, std::string loc);
	Alert(bool valid_alert);
};

class System_Alerts
{
public:
	void push(Alert);
	Alert pop();
	static System_Alerts* get_instance();
	int get_size_of_queue();
private:
	System_Alerts();
	std::vector<Alert> list_of_alerts;
	static System_Alerts* instance;

};

#endif // !SYSTEM_ALERTS_UTILITY_H


