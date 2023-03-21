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
	Internal_Message();
	virtual ~Internal_Message();
	virtual bool operator!=(Internal_Message* ptr_value);
	virtual bool operator==(Internal_Message* ptr_value);
	bool is_valid();
	virtual void validate();
protected:
	bool valid;
	unsigned long unique_message_id;
};

#endif