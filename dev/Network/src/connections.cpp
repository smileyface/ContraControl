#include "../system_interfaces/types/connections.h"	

const std::string local_connections::broadcast = "BROADCAST";
const std::string local_connections::local = "LOCAL";

void local_connections::setup(Network_Connection_List& list)
{
	list[broadcast] = Connection();
	list[local] = Connection();
}