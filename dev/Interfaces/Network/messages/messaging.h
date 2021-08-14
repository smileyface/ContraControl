#ifndef NETWORK_MESSAGES
#define NETWORK_MESSAGES

#include <cstring>

enum class MESSAGES : char
{
	NODE_HELLO,
	NODE_GOODBYE,
	UNDEFINED
};



struct MESSAGE_HEADER { char message_start = 0x65; MESSAGES message_id = MESSAGES::UNDEFINED; unsigned short length = 6; };
struct MESSAGE_FOOTER { char chk1 = 0x00; char chk2= 0x00; };
struct MESSAGE { };
struct PACKED_MESSAGE
{
	MESSAGE_HEADER header;
	MESSAGE* message = 0;
	MESSAGE_FOOTER footer;
	PACKED_MESSAGE() {};
	PACKED_MESSAGE(MESSAGE* message);
	MESSAGES get_message_enum_by_type();

};
struct Message_String
{
	unsigned short length;
	char* str;
	Message_String() { length = 0; str = '\0'; }
	Message_String(const char* string)
	{
		std::memcpy(str, string, sizeof(string));
		length = sizeof(string);
	}
};

unsigned char* pack();


#endif // !NETWORK_MESSAGES