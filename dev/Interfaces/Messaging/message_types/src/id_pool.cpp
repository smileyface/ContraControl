#include "../id_pool.h"

ID_Pool::ID_Pool() :
	id(0)
{ }

ID_Type ID_Pool::get()
{
	return id++;
}

ID_Pool MESSAGE_ID;