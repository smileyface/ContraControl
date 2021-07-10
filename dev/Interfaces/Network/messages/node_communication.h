#include "messaging.h"

struct NODE_HELLO : MESSAGE
{ 
	char addr[4];
	unsigned short id_length; 
	char* node_id;

	NODE_HELLO(char* id)
	{
		id_length = sizeof(id);
		node_id = id;
	}
};

