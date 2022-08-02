/*****************************************************************//**
 * \file   option_view_type.h
 * \brief
 *
 * \author kason
 * \date   August 2022
 *********************************************************************/

#ifndef VIEW_LOG_VIEW_TYPE
#define VIEW_LOG_VIEW_TYPE

#include "Messaging/consumers.h"

 /** A UI type for nandling options*/
class Option_View_Type
{
public:
	Option_View_Type();
	/**The log message captured from the message relay.*/
	struct MESSAGE
	{
		std::vector<std::string> OPTIONS;///<Log message.
	} message;///<Instance of the captured message.
	/**Get the log message from the message relay.*/
	void get_message();

protected:
	/**
	* .Message Consumer
	*/
	Message_Consumer* option_consumer;
	/** Stale view*/
	bool option_stale = true;
};
#endif // !VIEW_LOG_VIEW_TYPE
