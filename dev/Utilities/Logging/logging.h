#ifndef CC_LOGGING_MAIN_H
#define CC_LOGGING_MAIN_H

#include <queue>
#include "log_item.h"

/**
 Logging structure for holding Log_Entries.
 */
class Logger {
public:
	/**
	 Static access method.
	 \return Pointer to the logger instance
	 */
	static Logger* getInstance();

	/**
	 Add Log Entry to the logger.
	 \param priority Severity of the log item. 
	 \param msg Logging message
	 \param device Location that the entry is coming from.
	 */
	void addItem(LOG_PRIORITY priority, std::string msg, std::string device);
	/**
	 Return the Log_Entry at the top of the list.  
	 It also removes the entry from the list.
	 \return Essentially the first entry in the list.
	 */
	Log_Entry pop();
	/**
	Return the Log_Entry at the bottom of the list.
	It also removes the entry from the list.
	\return Essentially the last entry in the list.
	*/
	Log_Entry drop();
private:
	Logger();
	static Logger* instance;
	std::deque<Log_Entry> logging;
};

/**
 The main logger interface. Use this when interacting with the logger. It saves from getting the instance over and over again.
 */
namespace sys_log {
	/**
	Add Log Entry to the logger.
	\param priority Severity of the log item.
	\param msg Logging message
	\param device Location that the entry is coming from.
	*/
	void log(LOG_PRIORITY priority, std::string msg, std::string  device);
	/**
	 Return the Log_Entry at the top of the list.
	 It also removes the entry from the list.
	 \return Essentially the first entry in the list.
	 */
	Log_Entry pop();
	/**
	Return the Log_Entry at the bottom of the list.
	It also removes the entry from the list.
	\return Essentially the last entry in the list.
	*/
	Log_Entry drop();

};




#endif // !LOGGING_MAIN_H