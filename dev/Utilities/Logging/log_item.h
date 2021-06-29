/*****************************************************************//**
 * \file   log_item.h
 * \brief  
 * 
 * \author kason
 * \date   June 2021
 *********************************************************************/
#ifndef LOG_ITEM_H
#define LOG_ITEM_H

#include <string>
#include <vector>

/**
 Level of the entry.
 */
enum class LOG_PRIORITY {
	/**
	 A program breaking error.
	 */
	SEVERE,
	/**
	 Informational log entry. For verbose logging.
	 */
	INFO,
	/**
	 Debug level entry. For very verbose logging.
	 */
	DEBUG,
	/**
	 A non-program stopping error. 
	 */
	ERROR
};

/**
 Entry into the logger.
 */
class Log_Entry
{
public:
	Log_Entry() {
		priority = LOG_PRIORITY::ERROR;
		message = "NO MESSAGE";
		device = "SYSTEM ERROR";
	}
	/**
	 Setter constructor.
	 \param pri Type of entry.
	 \param msg Message of this entry.
	 \param dev Location in the code where this entry was created.
	 */
	Log_Entry(LOG_PRIORITY pri, std::string msg, std::string dev)
	{
		priority = pri;
		message = msg;
		device = dev;
	};
	/**
	 Type of entry.
	 */
	LOG_PRIORITY priority;
	/**
	 Message of this entry.
	 */
	std::string message;
	/**
	 Location in the code where this entry was created.
	 */
	std::string device;
private:

};




#endif