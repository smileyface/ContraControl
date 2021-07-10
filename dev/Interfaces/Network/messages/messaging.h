#ifndef NETWORK_MESSAGES
#define NETWORK_MESSAGES


#include <vector>

typedef std::vector<char> BUFFER;

enum class MESSAGES : char
{
	NODE_HELLO,
	NODE_GOODBYE,
	UNDEFINED
};

struct MESSAGE_HEADER { char message_start = 0x65; MESSAGES message_id; unsigned short length; };
struct MESSAGE_FOOTER { char chk1; char chk2; };
struct MESSAGE 
{ 
};

#endif // !NETWORK_MESSAGES