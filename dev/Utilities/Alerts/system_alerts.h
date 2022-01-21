#ifndef SYSTEM_ALERTS_UTILITY_H
#define SYSTEM_ALERTS_UTILITY_H

#include <vector>

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

char* alert_priority_as_string(ALERT_PRIORITY al);


struct Alert
{
	ALERT_PRIORITY priority;
	char* message;
	char* location;
};

class System_Alerts
{
public:
	void push(Alert);
	Alert pop();
	static System_Alerts* get_instance();
private:
	System_Alerts();
	std::vector<Alert> list_of_alerts;
	static System_Alerts* instance;

};

#endif // !SYSTEM_ALERTS_UTILITY_H


