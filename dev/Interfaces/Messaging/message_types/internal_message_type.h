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
	Internal_Message() :
		valid(false)
	{ }
	virtual ~Internal_Message()
	{ };
	/** This will be replaced when I come up with more messaging design */
	virtual bool operator!=(Internal_Message* ptr_value)
	{
		return this != ptr_value;
	}

	bool is_valid()
	{
		return valid;
	}

	virtual void validate()
	{
		valid = true;
	}
protected:
	bool valid;
};

#endif