/*****************************************************************//**
 * \file   node_type.h
 * \brief  
 * 
 * \author kason
 * \date   October 2023
 *********************************************************************/

#ifndef NODE_TYPE_ENUM
#define NODE_TYPE_ENUM

 /**
  Type of node, such as UI, GENERIC_HARDWARE or R-PI
  */
enum class NODE_TYPE : uint8_t
{
	/**
	 A Tester node.
	 */
	TEST,
	/**
	 A UI node. Connects to virtual devices
	 */
	UI,
	/**
	 Invalid node. Undefined.
	 */
	INVALID
};

#endif // !NODE_TYPE_ENUM
