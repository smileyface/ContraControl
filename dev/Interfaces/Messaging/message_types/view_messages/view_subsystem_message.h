/*******************************************************************//**
 * \file   view_subsystem_message.h
 * \brief
 *
 * \author kason
 * \date   July 2022
 *********************************************************************/
#ifndef VIEW_SUBSYSTEM_MESSAGE
#define VIEW_SUBSYSTEM_MESSAGE

#include "../internal_message_type.h"
#include "../Interfaces/Interfaces/enums/subsystem_enum.h"


/** A message for the view system. */
class View_Subsystem_Message : public Internal_Message
{
public:
	void placeholder();
	/**
	 * \param sender Subsystem sending the message. This is so we know who to send return messages to.
	 */
	void set_sender(SUBSYSTEM_ID_ENUM sender);
	/**
	 * \return Subsystem sending the message. This is so we know who to send return messages to.
	 */
	SUBSYSTEM_ID_ENUM get_sender();
private:
	SUBSYSTEM_ID_ENUM request_from;
};

#endif // !VIEW_FORMAT_MESSAGE
