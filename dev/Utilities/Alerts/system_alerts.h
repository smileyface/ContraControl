#ifndef SYSTEM_ALERTS_UTILITY_H
#define SYSTEM_ALERTS_UTILITY_H

#include <vector>
#include <string>


#include "Alerts/consumers.h"

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
	std::vector<Alert> pop(Message_Consumer*);
	static System_Alerts* get_instance();
	int get_size_of_queue();
	void register_consumer(Message_Consumer*);
private:
	System_Alerts();
	std::vector<std::pair<Alert, Consumer_List>> list_of_alerts;
	std::vector<Message_Consumer*> list_of_registered_consumers;
	static System_Alerts* instance;

};

#endif // !SYSTEM_ALERTS_UTILITY_H


