#include "../system_interfaces/types/connections.h"	

const std::string local_connections::broadcast = "BROADCAST";
const std::string local_connections::local = "LOCAL";

void local_connections::setup(network_connection_list& list)
{
	list[broadcast] = connection();
	list[local] = connection();
}