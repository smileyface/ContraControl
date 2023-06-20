/****************************************************************//**
* \file   id_pool.h
* \brief
*
* \author kason
* \date   March 2023
* ********************************************************************/

#ifndef ID_POOL_BLOCK
#define ID_POOL_BLOCK

typedef unsigned long ID_Type;

class ID_Pool
{
public:
	ID_Pool();
	ID_Type get();
private:
	ID_Type id;
};

extern ID_Pool MESSAGE_ID;

#endif // !ID_POOLS