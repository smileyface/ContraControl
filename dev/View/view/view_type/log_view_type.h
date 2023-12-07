/*****************************************************************//**
 * \file   log_view_type.h
 * \brief
 *
 * \author kason
 * \date   August 2022
 *********************************************************************/

#ifndef VIEW_LOG_VIEW_TYPE
#define VIEW_LOG_VIEW_TYPE

#include "Messaging/consumers.h"

/** A UI type for viewing logs*/
class Log_View_Type
{
public:
	Log_View_Type();
	virtual ~Log_View_Type();
	/**The log message captured from the message relay.*/
	struct MESSAGE
	{
		std::string MESSAGE;///<Log message.
		std::string LOC;///<Location message was sent from.
		std::string LEVEL;///<Level of log.
		bool vaild; ///<Is the message valid.
	};
	std::vector<MESSAGE> log_messages;///<Instance of the captured message.
	std::vector<std::string> painted_messages;///<Instance of the captured message formatted for display.
	/**Get the log message from the message relay.*/
	void get_message();
	/** Create the Log View */
	void create();
	/** Destroy the Log View */
	void destroy();

protected:    
	/**
	* .Message Consumer
	*/
	Message_Consumer* log_consumer;

};
#endif // !VIEW_LOG_VIEW_TYPE
