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
	 * Not equal comparator.
	 * @param ptr_value Right address.
	 * @return If left address is not equal to right address.
	 */
	virtual bool operator!=(Internal_Message* ptr_value);
	/**
	 * Equal comparator.
	 * @param ptr_value Right address.
	 * @return If left address is equal to the right address.
	 */
	virtual bool operator==(Internal_Message* ptr_value);
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
	/**
	 * A unique id for the message for comparisons.
	 */
	unsigned long unique_message_id;
};

#endif