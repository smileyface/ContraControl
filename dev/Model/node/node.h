#include <map>
#include <string>
#include "../device.h"

typedef std::string Node_Id

class Node
{
private:
	Connection connections;
	std::map<Node_Id, Device> devices;
};