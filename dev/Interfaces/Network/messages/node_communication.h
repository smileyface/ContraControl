#include "messaging.h"

struct NODE_HELLO : MESSAGE
{ 
	char addr[4]; 
	Message_String id;
};

