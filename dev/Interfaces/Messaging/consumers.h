/*****************************************************************//**
 * \file   consumers.h
 * \brief
 *
 * \author kason
 * \date   June 2021
 *********************************************************************/
#ifndef MESSAGE_CONSUMER_H
#define MESSAGE_CONSUMER_H

#include <vector>

/**
 * An object for declaring that the containing object wants to be notified of a change, or recieve a message sent.
 */
struct Message_Consumer
{
	/**
	 * Set consumer up with a flag that determines if it's got a message available
	 * \param stale Reference to the message indicator flag.
	 */
	Message_Consumer(bool& stale);
	/**
	 * Notify the containing object that a message has been recieved.
	 */
	void notify();
	/**
	 * Remove notification. To be done after containing object has handled the message.
	 */
	void freshen();

private:
	bool* stale;
};
/**
 * List of a message consumer. For use in message producers.
 */
typedef std::vector<Message_Consumer*> Consumer_List;
#endif
