#ifndef LOGGING_MESSAGE_TYPE
#define LOGGING_MESSAGE_TYPE
#include <string>

#include "internal_message_type.h"

/**
 Level of the message.
 */
enum class MESSAGE_PRIORITY
{
	/**
	Debug message. For very verbose logging.
	*/
	DEBUG_MESSAGE,
	/**
	Informational message. For verbose logging.
	*/
	INFO_MESSAGE,
	/**
	A non-program stopping error.
	*/
	ERROR_MESSAGE,
	/**
	A program breaking error.
	*/
	SEVERE_MESSAGE
};

/**
 * System level messsages
 */
class Logging_Message : public Internal_Message
{
public:

	/**
	 * \return text of the message.
	 */
	std::string get_message();
	/**
	 * \return location.
	 */
	std::string get_location();
	/**
	 * \return string of priority
	 */
	std::string get_priority_string();
	/**
	 * \return priority
	 */
	MESSAGE_PRIORITY get_priority();
	/**
	 * Create a new message with defined priority, message, and location.
	 *
	 * This is the standard way of creating a message.
	 * Message validity is set to true.
	 * \param pri Priority of the message
	 * \param msg Message to be sent
	 * \param loc Sender of this message
	 */
	Logging_Message(MESSAGE_PRIORITY pri, std::string msg, std::string loc);
	/**
	 * Create an empty message with a defined validity.
	 * \param valid_message Desired validity to set message to.
	 */
	Logging_Message(bool valid_message);

	void placeholder()
	{ };
private:
	/**
	 * How dire this message is.
	 */
	MESSAGE_PRIORITY priority;
	/**
	 * Message to be sent.
	 */
	std::string message;
	/**
	 * Where this message is from.
	 */
	std::string location;
};
#endif