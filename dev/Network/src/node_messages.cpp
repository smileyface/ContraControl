#include "../messages/node_communication.h"

MESSAGE Node_Messages::Network_Message_Factory(MESSAGES message)
{
	switch (message)
	{
	case MESSAGES::NODE_HELLO:
		return MESSAGE(message, { new Network_Address(), new Network_String() });
	}
}