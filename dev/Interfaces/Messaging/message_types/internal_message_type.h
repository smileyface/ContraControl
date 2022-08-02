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
	virtual ~Internal_Message()
	{ };
	/** This will be replaced when I come up with more messaging design */
	virtual void placeholder() = 0;
};

#endif