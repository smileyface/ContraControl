/*****************************************************************//**
 * \file   node_communication.h
 * \brief  
 * 
 * \author kason
 * \date   October 2021
 *********************************************************************/
#ifndef NETWORK_NODE_MESSAGES
#define NETWORK_NODE_MESSAGES
#include "messaging.h"

#include "types/network_message_types.h"

namespace Node_Messages
{
	MESSAGE Network_Message_Factory(MESSAGES message);
}
#endif
