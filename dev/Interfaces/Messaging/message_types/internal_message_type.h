/*******************************************************************//**
 * \file   internal_message_type.h
 * \brief
 *
 * \author kason
 * \date   June 2022
 *********************************************************************/

#ifndef INTERNAL_MESSAGE_BASE_TYPE
#define INTERNAL_MESSAGE_BASE_TYPE

 /**
  * Base class for internal messaging.
  */
class Internal_Message
{
public:
	/**
	 * Default Constructor
	 */
	Internal_Message();
	/**
	 * Default Deconstructor
	 */
	virtual ~Internal_Message();

	/**
	* Is the message valid.
	* @return Validity of the message.
	*/
	bool is_valid();
	/**
	 * Validate the message. Sets the valid flag.
	 */
	virtual void validate();
protected:
	/**
	 * Message validation flag.
	 */
	bool valid;
};

#endif