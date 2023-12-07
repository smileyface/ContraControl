#include <iostream>

#include "../console_format/console_log_view.h"
#include "../view_type/log_view_type.h"

#include "Messaging/message_relay.h"

Log_View_Type::Log_View_Type()
{
	log_consumer = Message_Relay::get_instance()->register_consumer<Logging_Message>();
}
Log_View_Type::~Log_View_Type()
{ 
	Message_Relay::get_instance()->deregister_consumer(log_consumer);
}
void Log_View_Type::get_message()
{
	for(Logging_Message messages = Message_Relay::get_instance()->pop<Logging_Message>(log_consumer); messages.is_valid() != false; messages = Message_Relay::get_instance()->pop<Logging_Message>(log_consumer))
	{
		MESSAGE message;
		message.MESSAGE = messages.get_message();
		message.LOC = messages.get_location();
		message.LEVEL = messages.get_priority_string();
		message.vaild = message.MESSAGE == "" ? false : true;
		log_messages.push_back(message);
	}
}
void Log_View_Type::create()
{

}
void Log_View_Type::destroy()
{ 

}
