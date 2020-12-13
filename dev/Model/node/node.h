#include <map>
#include <string>
#include "../device.h"

typedef std::string Node_Id
/*
This is probably a place holder
*/
struct Connection
{
	std::string address;
	int port;

};

class Node
{
private:
	Connection connections;
	std::map<Node_Id, Device> devices;
};