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

class View_Subsystem_Message : public Internal_Message
{
public:
	void placeholder();
	void set_sender(SUBSYSTEM_ID_ENUM sender);
	SUBSYSTEM_ID_ENUM get_sender();
private:
	SUBSYSTEM_ID_ENUM request_from;
};

#endif // !VIEW_FORMAT_MESSAGE
